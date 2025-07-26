#pragma once

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <unordered_map>
#include "CoreTypes.h"
#include "EventDispatcher.h"
#include "IEventListener.h"
#include "json.hpp"

class GameObject;

class Component
{
public:
	Component() = default;
	virtual ~Component() = default;
	virtual void Update(float deltaTime) = 0;
	virtual void OnEvent(EventType type, const void* data) abstract;
	virtual std::string GetTypeName() = 0;

	void HandleMessage(myCore::MessageID msg, void* data)
	{
		auto it = m_MessageHandlers.find(msg);
		if (it != m_MessageHandlers.end())
		{
			for (auto& handler : it->second)
			{
				handler(data);
			}
		}
	}

	virtual void Serialize(nlohmann::json& j) const = 0;
	virtual void Deserialize(const nlohmann::json& j) = 0;

	using HandlerType = std::function<void(void*)>;
	void RegisterMessageHandler(myCore::MessageID msg, HandlerType handler)
	{
		m_MessageHandlers[msg].emplace_back(std::move(handler));
	}

	void SetOwner(GameObject* owner) { m_Owner = owner; }

protected:
	GameObject* m_Owner = nullptr;
	std::unordered_map<myCore::MessageID, std::vector<HandlerType>> m_MessageHandlers;
	EventDispatcher& GetEventDispatcher() const;
};

using ComponentCreateFunc = std::function<std::unique_ptr<Component>()>;

class ComponentFactory
{
public:
	static ComponentFactory& Instance()
	{
		static ComponentFactory instance;
		return instance;
	}

	void Register(const std::string& typeName, ComponentCreateFunc func)
	{
		factoryMap[typeName] = func;
	}

	std::unique_ptr<Component> Create(const std::string& typeName)
	{
		if (factoryMap.find(typeName) != factoryMap.end())
		{
			return factoryMap[typeName]();
		}
		return nullptr;
	}

private:
	std::unordered_map<std::string, ComponentCreateFunc> factoryMap;
};


#define REGISTER_COMPONENT(TYPE) \
    namespace { \
        struct TYPE##Registrator { \
            TYPE##Registrator() { \
                ComponentFactory::Instance().Register(#TYPE, []() -> std::unique_ptr<Component> { return std::make_unique<TYPE>(); }); \
            } \
        }; \
        static TYPE##Registrator global_##TYPE##Registrator; \
    }