#pragma once

namespace dae {
	class GameObject;
}

class Component
{
public:
	virtual ~Component() = default;
	Component(const Component&) = delete;
	Component(Component&&) = delete;
	Component& operator=(const Component&) = delete;
	Component& operator=(Component&&) = delete;

	virtual void Update(float deltaTime) = 0;
	virtual void Render() {}

	void SetOwner(dae::GameObject* owner) {
		m_owner = owner;
	}

protected:
	explicit Component(dae::GameObject* owner = nullptr) : m_owner(owner) {}
	dae::GameObject* GetOwner() const { return m_owner; }

	dae::GameObject* m_owner = nullptr;
};