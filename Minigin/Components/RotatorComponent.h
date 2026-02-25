#pragma once
#include "Component.h"
#include <glm/glm.hpp>
#include <cmath>
#include "GameObject.h"

class RotatorComponent : public Component
{
public:
	RotatorComponent(float radius, float speed, glm::vec3 center = glm::vec3(0.f, 0.f, 0.f))
		: m_radius(radius)
		, m_speed(speed) 
		, m_center(center)
	{

	}

	void Update(float deltaTime) override
	{
		m_angle += m_speed * deltaTime;
		glm::vec3 pos{};
		pos.x = m_center.x + std::cos(m_angle) * m_radius;
		pos.y = m_center.y + std::sin(m_angle) * m_radius;
		GetOwner()->SetLocalPosition(pos);
	}

private:
	glm::vec3 m_center{};
	float m_radius;
	float m_speed;
	float m_angle{ 0.f };
};