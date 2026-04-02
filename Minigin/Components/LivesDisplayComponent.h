#pragma once

#include "../Component.h"
#include "../Event/IObserver.h"
#include "../Event/GameEvents.h"
#include "TextComponent.h"
#include "HealthComponent.h"

class LivesDisplayComponent : public Component, public IObserver
{
public:
	LivesDisplayComponent(HealthComponent* healthComponent, TextComponent* textComponent)
		: m_health(healthComponent)
		, m_text(textComponent)
	{
		m_health->GetSubject()->AddObserver(this);
	}

	~LivesDisplayComponent()
	{
		m_health->GetSubject()->RemoveObserver(this);
	}

	void Update(float /*deltaTime*/) override
	{

	}

	void Notify(unsigned int event) override
	{
		if (event == static_cast<unsigned int>(GameEvent::PlayerDied))
		{
			m_text->SetText("Lives: " + std::to_string(m_health->GetLives()));
		}
	}

private:
	HealthComponent* m_health;
	TextComponent* m_text; 
};