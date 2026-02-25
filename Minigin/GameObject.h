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
		void RemoveComponent(std::unique_ptr<Component> component);

		//Check whether a component has been added
		//TODO

		//W02
		//Scenegraph
		void SetParent(GameObject* parent, bool keepWorldPosition = true);
		GameObject* GetParent() const { return m_parent; }
		int GetChildCount() const { return static_cast<int>(m_children.size()); }
		GameObject* GetChildAt(int index) const { return m_children[index]; }

		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetWorldPosition();

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture{};

		std::vector<std::unique_ptr<Component>> m_components;

		GameObject* m_parent;
		std::vector<GameObject*> m_children{};

		bool m_positionIsDirty{ true };

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		bool IsChild(GameObject* go) const;
		void SetPositionDirty();
		void UpdateWorldPosition();
	};
}
