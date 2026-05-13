#pragma once

#include "Command.h"
#include "../Sound/ServiceLocator.h"

namespace dae {
	class PlaySoundCommand final : public Command {
		unsigned short m_id;
		float m_volume;

	public:
		PlaySoundCommand(unsigned short id, float volume)
			: m_id(id)
			, m_volume(volume)
		{}

		void Execute() override {
			ServiceLocator::GetSoundSystem().Play(m_id, m_volume);
		}
	};
}