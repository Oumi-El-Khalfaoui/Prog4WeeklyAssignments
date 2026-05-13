#include "SDLSoundSystem.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <string>

namespace dae {
    struct SoundRequest {
        sound_id id;
        float volume;
    };

    struct SDLSoundSystem::Impl {
        MIX_Mixer* m_Mixer{ nullptr };
        std::unordered_map<sound_id, std::string>  m_Paths;
        std::unordered_map<sound_id, MIX_Audio*>   m_Audio;

        std::queue<SoundRequest>    m_Queue;
        std::mutex                  m_Mutex;
        std::condition_variable     m_CV;
        std::thread                 m_Thread;
        bool                        m_Quit{ false };

        Impl() {
            MIX_Init();

            // output device
            int count = 0;
            SDL_AudioDeviceID* devices = SDL_GetAudioPlaybackDevices(&count);
            SDL_AudioDeviceID deviceID = (devices && count > 0) ? devices[0] : SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK;
            SDL_free(devices);

            m_Mixer = MIX_CreateMixerDevice(deviceID, nullptr);
            if (!m_Mixer)
                SDL_Log("MIX_CreateMixerDevice failed: %s", SDL_GetError());

            m_Thread = std::thread([this]() { ProcessLoop(); });
        }

        ~Impl() {
            {
                std::lock_guard lock(m_Mutex);
                m_Quit = true;
            }
            m_CV.notify_one();
            m_Thread.join();

            for (auto& [id, audio] : m_Audio)
                MIX_DestroyAudio(audio);

            MIX_DestroyMixer(m_Mixer);
            MIX_Quit();
        }

        void Enqueue(sound_id id, float volume) {
            {
                std::lock_guard lock(m_Mutex);
                m_Queue.push({ id, volume });
            }
            m_CV.notify_one();
        }

        void ProcessLoop() {
            while (true) {
                std::unique_lock lock(m_Mutex);
                m_CV.wait(lock, [this] { return !m_Queue.empty() || m_Quit; });

                if (m_Quit && m_Queue.empty()) return;

                SoundRequest req = m_Queue.front();
                m_Queue.pop();
                lock.unlock();

                if (!m_Audio.contains(req.id)) {
                    auto it = m_Paths.find(req.id);
                    if (it != m_Paths.end())
                        m_Audio[req.id] = MIX_LoadAudio(m_Mixer, it->second.c_str(), true);
                }

                auto it = m_Audio.find(req.id);
                if (it == m_Audio.end() || it->second == nullptr) continue;

                MIX_Track* track = MIX_CreateTrack(m_Mixer);
                if (!track) continue;

                MIX_SetTrackAudio(track, it->second);
                MIX_SetTrackGain(track, req.volume);
                MIX_SetTrackStoppedCallback(track, &Impl::OnTrackStopped, nullptr);
                MIX_PlayTrack(track, 0);
            }
        }

        static void OnTrackStopped(void* /*userdata*/, MIX_Track* t) {
            MIX_DestroyTrack(t);
        }
    };
} 

dae::SDLSoundSystem::SDLSoundSystem()
    : m_pImpl(std::make_unique<Impl>()) {}

dae::SDLSoundSystem::~SDLSoundSystem() = default;

void dae::SDLSoundSystem::Play(sound_id id, float volume) {
    m_pImpl->Enqueue(id, volume);
}

void dae::SDLSoundSystem::LoadSound(sound_id id, const std::string& path) {
    std::lock_guard lock(m_pImpl->m_Mutex);
    m_pImpl->m_Paths[id] = path;
}