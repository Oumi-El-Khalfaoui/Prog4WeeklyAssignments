#pragma once

#include "../Event/IObserver.h"
#include "../Event/GameEvents.h"
#include "ServiceLocator.h"

enum SoundId : unsigned short {
	SFX_PLAYER_DIED = 0,
	SFX_POINTS = 1,
	SFX_ENEMY_DIED = 2,
	SFX_PICKUP = 3
};

class SoundObserver final : public IObserver {
public:
	void Notify(unsigned int event) override {
		auto& ss = dae::ServiceLocator::GetSoundSystem();

		switch (static_cast<GameEvent>(event))
		{
		case GameEvent::PlayerDied:
			ss.Play(SFX_PLAYER_DIED, 1.f);
			break;
		case GameEvent::PlayerGainedPoints:
			ss.Play(SFX_POINTS, 0.8f);
			break;
		case GameEvent::EnemyDied:
			ss.Play(SFX_ENEMY_DIED, 1.f);
			break;
		case GameEvent::PickupCollected:
			ss.Play(SFX_PICKUP, 0.9f);
			break;
		}
	}
};