#include "Obstacle.h"
#include "BoxColliderComponent.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"

Obstacle::Obstacle(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	m_Collider = AddComponent<BoxColliderComponent>();
	m_Collider->Start();
	m_Collider->SetSize(Vec2F(100, 100));
	m_Sprite = GetComponent<SpriteRenderer>();
	m_Z = 1;

	//std::function<void(const CollisionInfo&)>
	//using StateFunc = std::function<void()>;
	//using StateFuncFloat = std::function<void(float)>;

	/*
					[this](float dt)
				{
					this->m_KickCool += dt;
					if (this->m_KickCool >= 2.0f)
					{
						this->m_KickCool = 0;
						this->GetFSM().Trigger("Kick");
					}
				}
	*/

	m_Collider->GetFSM().ChangeState("Stay");

	m_Collider->SetOnStay(
		[this](const CollisionInfo& info)
		{
			if (info.self != this->GetComponent<BoxColliderComponent>())
				return;
			auto trans = this->GetComponent<TransformComponent>();
			trans->Translate(Vec2F(0.1f, 0));
		}
	);
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