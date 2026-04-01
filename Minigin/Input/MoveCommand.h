#pragma once

#include "Command.h"
#include "../GameObject.h"
#include <glm/glm.hpp>

namespace dae
{
	class MoveCommand final : public Command
	{
	public:
		MoveCommand(GameObject* pTarget, glm::vec3 direction, float speed)
			: m_pTarget(pTarget)
			, m_direction(direction)
			, m_speed(speed)
		{ }

		void Execute() override
		{
			auto pos = m_pTarget->GetWorldPosition();
			pos += m_direction * m_speed;
			m_pTarget->SetLocalPosition(pos);
		}

	private:
		GameObject* m_pTarget;
		glm::vec3 m_direction;
		float m_speed;
	};
}