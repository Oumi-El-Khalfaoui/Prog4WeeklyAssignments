#pragma once

#include "../Component.h"
#include "../Texture2D.h"
#include "../Renderer.h"
#include <memory>

enum class AnimationState
{
	Idle,
	WalkUp,
	WalkDown,
	WalkLeft,
	WalkRight
};

struct Animation
{
	std::shared_ptr<dae::Texture2D> texture;
	int frameCount;
	float frameTime;
};

class SpriteAnimatorComponent : public Component
{
public:
	SpriteAnimatorComponent() = default;

	void Update(float deltaTime) override
	{
		if (!m_movedThisFrame)
		{
			m_state = AnimationState::Idle;
		}

		auto it = m_animations.find(m_state);
		if (it == m_animations.end())
		{
			return;
		}

		const Animation& anim = it->second;
		
		m_elapsed += deltaTime;

		if (m_elapsed >= anim.frameTime)
		{
			m_elapsed -= anim.frameTime;
			m_currentFrame = (m_currentFrame + 1) % anim.frameCount;
		}

		m_movedThisFrame = false;
	}

	void Render() override
	{
		auto it = m_animations.find(m_state);
		if (it == m_animations.end())
		{
			return;
		}

		const Animation& anim = it->second;
		const auto& pos = GetOwner()->GetWorldPosition();

		float totalWidth{}, height{};
		SDL_GetTextureSize(anim.texture->GetSDLTexture(), &totalWidth, &height);

		float frameWidth = totalWidth / anim.frameCount;

		SDL_FRect src{};
		src.x = m_currentFrame * frameWidth;
		src.y = 0.f;
		src.w = frameWidth;
		src.h = height;

		dae::Renderer::GetInstance().RenderTexture(*anim.texture, pos.x, pos.y, src);
	}

	void SetState(AnimationState newState)
	{
		m_movedThisFrame = true;

		if (m_state == newState)
		{
			return;
		}

		m_state = newState;
		m_currentFrame = 0;
		m_elapsed = 0;
	}

	void AddAnimation(AnimationState state, const Animation& anim)
	{
		m_animations[state] = anim;
	}

private:
	std::unordered_map<AnimationState, Animation> m_animations;
	int m_currentFrame = 0;
	float m_elapsed = 0.f;
	AnimationState m_state{ AnimationState::Idle };
	bool m_movedThisFrame{ false };
};