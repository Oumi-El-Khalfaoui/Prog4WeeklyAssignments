#pragma once

#include "../Component.h"
#include "../Event/IObserver.h"
#include "../Event/GameEvents.h"
#include "TextComponent.h"
#include "ScoreComponent.h"

class ScoreDisplayComponent : public Component, public IObserver 
{
public:
	ScoreDisplayComponent(ScoreComponent* scoreComponent, TextComponent* textComponent)
		: m_score(scoreComponent)
		, m_text(textComponent)
	{
		m_score->GetSubject()->AddObserver(this);
	}

	~ScoreDisplayComponent()
	{
		m_score->GetSubject()->RemoveObserver(this);
	}

	void Update(float /*deltaTime*/) override
	{

	}

	void Notify(unsigned int event) override
	{
		if (event == static_cast<unsigned int>(GameEvent::PlayerGainedPoints))
		{
			m_text->SetText("Score: " + std::to_string(m_score->GetScore()));
		}
	}

private:
	ScoreComponent* m_score;
	TextComponent* m_text;
};