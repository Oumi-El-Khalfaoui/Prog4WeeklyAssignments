#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		[[nodiscard]] const glm::vec3& GetLocalPosition() const { return m_localPosition; }
		[[nodiscard]] const glm::vec3& GetWorldPosition() const { return m_worldPosition; }

		void SetLocalPosition(float x, float y, float z = 0);
		void SetLocalPosition(const glm::vec3& position);
		void SetWorldPosition(const glm::vec3& position) {
			m_worldPosition = position;
		}

	private:
		glm::vec3 m_localPosition;
		glm::vec3 m_worldPosition;
	};
}
