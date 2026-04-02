#pragma once

#include "../Component.h"
#include "../Event/GameEvents.h"
#include "../Event/Subject.h"
#include <memory>

class ScoreComponent : public Component
{
public:
	ScoreComponent() 
		: m_subject(std::make_unique<Subject>()) 
		, m_score(0)
	{ }

	void Update(float /*deltaTime*/) override
	{

	}

	void AddPoints(int points)
	{
		m_score += points;
		m_subject->NotifyObservers(static_cast<unsigned int>(GameEvent::PlayerGainedPoints));
	}

	int GetScore() const
	{
		return m_score;
	}

	Subject* GetSubject() const
	{
		return m_subject.get();
	}

private:
	int m_score;
	std::unique_ptr<Subject> m_subject;
};