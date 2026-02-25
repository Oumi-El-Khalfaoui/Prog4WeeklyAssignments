#pragma once

namespace dae {
	class GameObject;
}

class Component
{
public:
	virtual ~Component() = default;
	virtual void Update(float /*deltaTime*/){}
	virtual void Render() {}

	void SetOwner(dae::GameObject* owner) {
		m_owner = owner;
	}

	dae::GameObject* m_owner = nullptr;
};