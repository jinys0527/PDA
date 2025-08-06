#pragma once
#include "EventDispatcher.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include "CoreTypes.h"
#include "Component.h"
#include "RenderData.h"

class Object
{
	friend class Scene;
	friend class TestScene;
	friend class TitleScene;
public:
	Object(EventDispatcher& eventDispatcher);
	virtual ~Object() = default;

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

	virtual void FixedUpdate();

	void SendMessages(const myCore::MessageID msg, void* data = nullptr);

	void SendEvent(const std::string& evt);

	EventDispatcher& GetEventDispatcher() const { return m_EventDispatcher; }

protected:
	std::string m_Name;
	std::unordered_map<std::string, std::unique_ptr<Component>> m_Components;
	EventDispatcher& m_EventDispatcher;
};

