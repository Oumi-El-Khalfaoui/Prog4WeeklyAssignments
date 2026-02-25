#include "Transform.h"

void dae::Transform::SetLocalPosition(const float x, const float y, const float z)
{
	m_localPosition.x = x;
	m_localPosition.y = y;
	m_localPosition.z = z;
}

void dae::Transform::SetLocalPosition(const glm::vec3& position) 
{ 
	m_localPosition = position; 
}