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
	friend class GameScene;
public:
	Object(EventDispatcher& eventDispatcher);
	virtual ~Object() = default;

	template<typename T, typename... Args>
	T* AddComponent(Args&&... args)
	{
		static_assert(std::is_constructible_v<T, Args...>, "Invalid constructor arguments for T.");

		auto comp = std::make_unique<T>(std::forward<Args>(args)...);
		comp->SetOwner(this);  // �ʿ��� ���
		T* ptr = comp.get();

		m_Components[T::StaticTypeName].emplace_back(std::move(comp));
		return ptr;
	}

	template<typename T>
	T* GetComponent(int index = 0) const
	{
		auto it = m_Components.find(T::StaticTypeName);
		if (it == m_Components.end())
			return nullptr;

		const auto& vec = it->second;
		if (index < 0 || index >= static_cast<int>(vec.size()))
			return nullptr;

		return dynamic_cast<T*>(vec[index].get());
	}

	template<typename T>
	std::vector<T*> GetComponents() const
	{
		std::vector<T*> result;

		auto it = m_Components.find(T::StaticTypeName);
		if (it == m_Components.end())
			return result; // �� ���� ��ȯ

		for (const auto& comp : it->second)
		{
			if (auto ptr = dynamic_cast<T*>(comp.get()))
				result.push_back(ptr);
		}

		return result;
	}

	virtual void Update(float deltaTime);

	virtual void FixedUpdate();

	void SetName(std::string name)
	{
		m_Name = name;
	}

	std::string GetName() const
	{
		return m_Name;
	}

	void SendMessages(const myCore::MessageID msg, void* data = nullptr);

	void SendEvent(const std::string& evt);

	EventDispatcher& GetEventDispatcher() const { return m_EventDispatcher; }

protected:
	std::string m_Name;
	std::unordered_map<std::string, std::vector<std::unique_ptr<Component>>> m_Components;
	EventDispatcher& m_EventDispatcher;
};

