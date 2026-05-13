#pragma once

#include "SoundSystem.h"
#include <memory>

namespace dae {
	class SDLSoundSystem final : public SoundSystem {
		struct Impl;
		std::unique_ptr<Impl> m_pImpl;

	public:
		SDLSoundSystem();
		~SDLSoundSystem() override;
		void Play(sound_id id, float volume) override;
		void LoadSound(sound_id id, const std::string& path) override;
	};
}