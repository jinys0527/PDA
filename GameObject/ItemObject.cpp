#include "ItemObject.h"
#include "BoxColliderComponent.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include <iostream>

ItemObject::ItemObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	m_Collider = AddComponent<BoxColliderComponent>();
	m_Collider->Start();
	m_Collider->SetSize(Vec2F(52, 112));
	m_Sprite = GetComponent<SpriteRenderer>();
	m_Z = 1;


	// �浹 ���� ( Enter -> (������ Exit �ȵǾ�����) -> Stay -> (�浹 ������) -> Exit -> (��� ȣ�� Exit�� ��ǻ� �������ٴ� state�� Ȯ���� �ð��� ����) -> None )

	m_Collider->GetFSM().SetOnEnter("Exit", [this]()
		{
			this->m_Collider->GetFSM().Trigger("None");
			std::cout << "Exit " << "����" << std::endl;
		});



	m_Collider->SetOnEnter(
		[this](const CollisionInfo& info)
		{
			if (info.self != this->GetComponent<BoxColliderComponent>())
				return;
            if(m_isBullet)
                this->GetEventDispatcher().Dispatch(EventType::OnPlayerReinforcedCollisionOccur, (const void*)-1);
            else
			    this->GetEventDispatcher().Dispatch(EventType::OnPlayerCollisonOccur, (const void*)-1);
			info.self->GetFSM().Trigger("CollisionEnter");
		}
	);

	m_Collider->SetOnStay(
		[this](const CollisionInfo& info)
		{
			if (info.self != this->GetComponent<BoxColliderComponent>())
				return;
			info.self->GetFSM().Trigger("CollisionStay");
			auto trans = this->GetComponent<TransformComponent>();
			trans->Translate(Vec2F(0.1f, 0));
		}
	);

	m_Collider->SetOnExit(
		[this](const CollisionInfo& info)
		{
			if (info.self != this->GetComponent<BoxColliderComponent>())
				return;
			info.self->GetFSM().Trigger("CollisionExit");
		}
	);
}

ItemObject::~ItemObject()
{
}

void ItemObject::Serialize(nlohmann::json& j) const
{
    j["name"] = m_Name;
    j["components"] = nlohmann::json::array();
    j["lane"] = m_Z;
    for (const auto& component : m_Components)
    {
        for (const auto& comp : component.second)
        {
            nlohmann::json compJson;
            compJson["type"] = comp->GetTypeName();
            comp->Serialize(compJson["data"]);
            j["components"].push_back(compJson);
        }
    }
}

void ItemObject::Deserialize(const nlohmann::json& j)
{
    m_Name = j.at("name");
    m_Z = j.at("lane");

    for (const auto& compJson : j.at("components"))
    {
        std::string typeName = compJson.at("type");

        // ���� ������Ʈ�� ������ ã�Ƽ� ����
        auto it = m_Components.find(typeName);
        if (it != m_Components.end() && !it->second.empty())
        {
            // �ش� Ÿ���� ��� ������Ʈ�� ���� Deserialize �õ�
            for (auto& comp : it->second)
            {
                comp->Deserialize(compJson.at("data"));
            }
        }
        else
        {
            // ������ ���� ���� �� �߰�
            auto comp = ComponentFactory::Instance().Create(typeName);
            if (comp)
            {
                comp->Deserialize(compJson.at("data"));
                AddComponent(std::move(comp));
            }
        }
    }
}