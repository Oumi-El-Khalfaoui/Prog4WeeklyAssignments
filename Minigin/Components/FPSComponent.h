#pragma once
#include "Component.h"
#include "TextComponent.h"
#include <chrono>

class FPSComponent : public Component
{
public:
	FPSComponent(TextComponent* textComponent)
		: m_textComponent(textComponent)
	{

	}

	virtual void Update(float deltaTime) override {
		float fps = 1.f / deltaTime;
		m_textComponent->SetText(std::to_string(fps));
	}

private:
	TextComponent* m_textComponent;
};