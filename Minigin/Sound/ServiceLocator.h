#pragma once

#include "SoundSystem.h"
#include <memory>

namespace dae {
	class NullSoundSystem final : public SoundSystem {
	public:
		void Play(sound_id, float) override {}
		void LoadSound(sound_id, const std::string&) override {}
	};

	class ServiceLocator final {
		static std::unique_ptr<SoundSystem> m_SoundSystem;
	public:
		static SoundSystem& GetSoundSystem() {
			return *m_SoundSystem;
		}

		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss) {
			m_SoundSystem = ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move(ss);
		}
	};
}