#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Render() const
{
	if (m_texture != nullptr) 
	{
		const auto& pos = m_transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}

	

	for (auto& component : m_components)
	{
		component->Render();
	}
}

void dae::GameObject::AddComponent(std::unique_ptr<Component> component)
{
	component->SetOwner(this);
	m_components.push_back(std::move(component));
}



/*void dae::GameObject::RemoveComponent(std::unique_ptr<Component> component)
{
	//m_components.erase();
}*/

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
