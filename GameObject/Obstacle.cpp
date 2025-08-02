#include "Obstacle.h"
#include "BoxColliderComponent.h"
#include "SpriteRenderer.h"

Obstacle::Obstacle(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	AddComponent<BoxColliderComponent>();
	AddComponent<SpriteRenderer>();
}

void Obstacle::Serialize(nlohmann::json& j) const
{
	j["name"] = m_Name;
	j["components"] = nlohmann::json::array();
	j["lane"] = m_Z;
	for (const auto& component : m_Components)
	{
		nlohmann::json compJson;
		compJson["type"] = component.second->GetTypeName();
		component.second->Serialize(compJson["data"]);
		j["components"].push_back(compJson);
	}
}

void Obstacle::Deserialize(const nlohmann::json& j)
{
	m_Name = j.at("name");
	m_Z = j.at("lane");

	for (const auto& compJson : j.at("components"))
	{
		std::string typeName = compJson.at("type");

		// 기존 컴포넌트가 있으면 찾아서 갱신
		auto it = std::find_if(m_Components.begin(), m_Components.end(),
			[&](const auto& pair)
			{
				return pair.second->GetTypeName() == typeName;
			});

		if (it != m_Components.end())
		{
			it->second->Deserialize(compJson.at("data"));
		}
		else
		{
			// 없으면 새로 생성 후 추가
			auto comp = ComponentFactory::Instance().Create(typeName);
			if (comp)
			{
				comp->Deserialize(compJson.at("data"));
				AddComponent(std::move(comp));
			}
		}
	}
}