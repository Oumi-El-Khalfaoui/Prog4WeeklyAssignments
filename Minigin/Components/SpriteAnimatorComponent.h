#pragma once

#include "../Component.h"
#include "../Texture2D.h"
#include "../Renderer.h"
#include <memory>



class SpriteAnimatorComponent : public Component
{
public:
	SpriteAnimatorComponent(std::shared_ptr<dae::Texture2D> spriteSheet, int frameCount, float frameTime)
		: m_spriteSheet(spriteSheet)
		, m_frameCount(frameCount)
		, m_frameTime(frameTime)
	{
		float totalWidth{}, height{};
		SDL_GetTextureSize(spriteSheet->GetSDLTexture(), &totalWidth, &height);
		m_frameWidth = totalWidth / frameCount;
		m_frameHeight = height;
	}

	void SetWalking(bool isWalking)
	{
		if (m_isWalking == isWalking)
		{
			return;
		}

		m_isWalking = isWalking;

		if (!isWalking)
		{
			m_currentFrame = 0;
			m_elapsed = 0.f;
		}
	}

	void Update(float deltaTime) override
	{
		if (!m_isWalking)
		{
			return;
		}

		m_elapsed += deltaTime;

		if (m_elapsed >= m_frameTime)
		{
			m_elapsed -= m_frameTime;
			m_currentFrame = (m_currentFrame + 1) % m_frameCount;

			if (m_currentFrame == 0)
			{
				m_currentFrame = (m_currentFrame + 1) % m_frameCount;
			}
		}

		m_isWalking = false;
	}

	void Render() override
	{
		const auto& pos = const_cast<dae::GameObject*>(GetOwner())->GetWorldPosition();

		SDL_FRect src{};
		src.x = m_currentFrame * m_frameWidth;
		src.y = 0.f;
		src.w = m_frameWidth;
		src.h = m_frameHeight;

		dae::Renderer::GetInstance().RenderTexture(*m_spriteSheet, pos.x, pos.y, src);
	}

private:
	std::shared_ptr<dae::Texture2D> m_spriteSheet;
	int m_frameCount;
	int m_currentFrame = 0;
	float m_frameTime;
	float m_elapsed = 0.f;
	float m_frameWidth{};
	float m_frameHeight{};
	bool m_isWalking{ false };

};