#pragma once

#include "../Component.h"
#include "../Event/GameEvents.h"
#include "../Event/Subject.h"
#include <memory>

class HealthComponent : public Component
{
public:
	explicit HealthComponent(int lives = 3)
		: m_lives(lives)
		, m_subject(std::make_unique<Subject>())
	{ }

	void Update(float) override {}

	void Die()
	{
		--m_lives;
		m_subject->NotifyObservers(static_cast<unsigned int>(GameEvent::PlayerDied));

	}

	int GetLives() const
	{
		return m_lives;
	}

	Subject* GetSubject() const
	{
		return m_subject.get(); // what is get()
	}
private:
	int m_lives;
	std::unique_ptr<Subject> m_subject;
};