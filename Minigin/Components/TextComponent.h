#pragma once
#include "TextObject.h"
#include "Component.h"

class TextComponent : public Component
{
public:
	TextComponent(std::shared_ptr<dae::TextObject> textObject)
		: m_textObject(textObject)
	{
	}

	virtual void Update(float deltaTime) override {
		if (m_needsUpdate)
		{
			m_textObject->Update(deltaTime);
		}
	}

	virtual void Render() override {
		m_textObject->Render();
	}

	void SetText(const std::string& text) {
		m_textObject->SetText(text);
		m_needsUpdate = true;
	}

private:
	std::shared_ptr<dae::TextObject> m_textObject;
	bool m_needsUpdate = true;
};