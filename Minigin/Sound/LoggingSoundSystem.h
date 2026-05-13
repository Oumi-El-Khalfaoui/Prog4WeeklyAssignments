#pragma once

#include "SoundSystem.h"
#include <memory>
#include <iostream>

namespace dae {
	class LoggingSoundSystem final : public SoundSystem {
		std::unique_ptr<SoundSystem> m_Real;

	public:
		explicit LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss)
			: m_Real(std::move(ss))
		{}

		void Play(sound_id id, float volume) override {
			m_Real->Play(id, volume);
			std::cout << "[Sound] Playing id = " << id << "; vol = " << volume << "\n";
		}

		void LoadSound(sound_id id, const std::string& path) override {
			m_Real->LoadSound(id, path);
			std::cout << "[Sound] Playing id = " << id << "; path = " << path << "\n";

		}
	};
}