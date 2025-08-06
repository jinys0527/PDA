#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include "CoreTypes.h"
#include "Component.h"
#include "EventDispatcher.h"
#include "json.hpp"
#include <vector>
#include "RenderData.h"

class TransformComponent;
class SpriteRenderer;

class GameObject
{
	friend class Editor;
	friend class Scene;
	friend class TestScene;
	friend class TitleScene;
public:
	GameObject(EventDispatcher& eventDispatcher);
	virtual ~GameObject() = default;

	template<typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		static_assert(std::is_constructible_v<T, Args...>, "Invalid constructor arguments for T.");
		auto comp = std::make_unique<T>(std::forward<Args>(args)...);
		comp->SetOwner(this);
		T* ptr = comp.get();
		m_Components[std::string(T::StaticTypeName)] = std::move(comp);
		return ptr;
	}

	void AddComponent(std::unique_ptr<Component> comp)	//Deserialize¿ë
	{
		comp->SetOwner(this);
		m_Components[comp->GetTypeName()] = std::move(comp);
	}

	template<typename T>
	T* GetComponent() const 
	{
		auto it = m_Components.find(T::StaticTypeName);
		if (it != m_Components.end())
		{
			return static_cast<T*>(it->second.get());
		}

		return nullptr;
	}

	virtual void Update(float deltaTime);
	virtual void Render(std::vector<RenderInfo>& renderInfo);
	virtual void FixedUpdate();

	void SendMessages(const myCore::MessageID msg, void* data = nullptr);
	
	void SendEvent(const std::string& evt);

	void Serialize(nlohmann::json& j) const;
	void Deserialize(const nlohmann::json& j);

	EventDispatcher& GetEventDispatcher() const { return m_EventDispatcher; }
protected:
	std::string m_Name;
	std::unordered_map<std::string, std::unique_ptr<Component>> m_Components;
	TransformComponent* m_Transform;
	EventDispatcher& m_EventDispatcher;
};

