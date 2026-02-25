#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Transform.h"
#include "Component.h"

namespace dae
{
	class Texture2D;
	class GameObject 
	{
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture{};
	public:
		virtual void Update(float deltaTime) {
			for (auto& component : m_components)
			{
				component->Update(deltaTime);
			}
		}
		virtual void Render() const;

		//W01 
		//Add component to game object
		void AddComponent(std::unique_ptr<Component> component);

		
		//Get a component from a game object
		template<typename T>
		T* GetComponent() {
			for (auto& component : m_components)
			{
				if (auto casted = dynamic_cast<T*>(component))
				{
					return casted;
				}
			}

			return nullptr;
		}


		//Remove a component from a game object in a safe manner
		//void RemoveComponent(std::unique_ptr<Component> component);

		//Check whether a component has been added
		//TODO

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::unique_ptr<Component>> m_components;
	};
}
