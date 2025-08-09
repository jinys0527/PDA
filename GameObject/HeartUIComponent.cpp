#include "HeartUIComponent.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "UIImageComponent.h"

HeartUIComponent::~HeartUIComponent()
{
	GetEventDispatcher().RemoveListener(EventType::OnPlayerHpChanged, this);
}

void HeartUIComponent::Start()
{
	GetEventDispatcher().AddListener(EventType::OnPlayerHpChanged, this);
}

void HeartUIComponent::Update(float deltaTime)
{
}

void HeartUIComponent::OnEvent(EventType type, const void* data)
{
	if (type == EventType::OnPlayerHpChanged)
	{
		auto comp = m_Owner->GetComponent<SpriteRenderer>();
		if (comp == nullptr)
		{
			auto comp2 = m_Owner->GetComponent<UIImageComponent>();

			if (m_HpLoc + 1 <= (int)data)
			{
				comp2->SetOpacity(1);
			}
			else
			{
				comp2->SetOpacity(0);
			}
		}
		else
		{
			if (m_HpLoc + 1 <= (int)data)
			{
				comp->SetOpacity(1);
			}
			else
			{
				comp->SetOpacity(0);
			}
		}
	}
}

void HeartUIComponent::Serialize(nlohmann::json& j) const
{
}

void HeartUIComponent::Deserialize(const nlohmann::json& j)
{
}
