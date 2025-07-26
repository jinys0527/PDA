#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"

GameObject::GameObject(EventDispatcher& eventDispatcher) : m_EventDispatcher(eventDispatcher)
{
	TransformComponent* trans = AddComponent<TransformComponent>();
}

void GameObject::Update(float deltaTime)
{
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		it->second->Update(deltaTime);
	}
}

TransformComponent* GameObject::RenderPosition()
{
	SpriteRenderer* sr = GetComponent<SpriteRenderer>();
	if (sr != nullptr)
	{
		//sr->Render();
		auto it = m_Components.find(typeid(TransformComponent));
		if (it != m_Components.end()) {
			return dynamic_cast<TransformComponent*>(it->second.get());
		}
	}
	return nullptr;
}

SpriteRenderer* GameObject::RenderTexture()
{
	auto it = m_Components.find(typeid(SpriteRenderer));
	if (it != m_Components.end())
	{
		return dynamic_cast<SpriteRenderer*>(it->second.get());
	}
	return nullptr;
}

void GameObject::Serialize(nlohmann::json& j) const
{
	j["name"] = m_Name;
	j["components"] = nlohmann::json::array();
	for (const auto& component : m_Components)
	{
		nlohmann::json compJson;
		compJson["type"] = component.second->GetTypeName();
		component.second->Serialize(compJson["data"]);
		j["components"].push_back(compJson);
	}
}

void GameObject::Deserialize(const nlohmann::json& j)
{
	m_Name = j.at("name");
	m_Components.clear();

	for (const auto& compJson : j.at("components"))
	{
		std::string typeName = compJson.at("type");
		auto comp = ComponentFactory::Instance().Create(typeName);
		if (comp)
		{
			comp->Deserialize(compJson.at("data"));
			AddComponent(std::move(comp));
		}
	}
}

void GameObject::SendMessages(const myCore::MessageID msg, void* data /* = nullptr */)
{
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		it->second->HandleMessage(msg, data);
	}
}


void GameObject::SendEvent(const std::string& evt)
{
	for (auto it = m_Components.begin(); it != m_Components.end(); it++)
	{
		//it->second->OnEvent(evt);
	}
}