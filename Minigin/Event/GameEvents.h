#pragma once

enum class GameEvent : unsigned int
{
	PlayerDied,
	PlayerGainedPoints,
	EnemyDied,
	PickupCollected
};