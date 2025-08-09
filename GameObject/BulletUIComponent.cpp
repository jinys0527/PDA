#include "BulletUIComponent.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include "UITextComponent.h"

BulletUIComponent::~BulletUIComponent()
{
	m_Owner->GetEventDispatcher().RemoveListener(EventType::OnPlayerReinforcedBulletChanged, this);
}

void BulletUIComponent::Start()
{
	m_Owner->GetEventDispatcher().AddListener(EventType::OnPlayerReinforcedBulletChanged, this);
}

void BulletUIComponent::Update(float deltaTime)
{
}

void BulletUIComponent::OnEvent(EventType type, const void* data)
{
	if (type == EventType::OnPlayerReinforcedBulletChanged)
	{
		auto comp = m_Owner->GetComponent<UITextComponent>();
		comp->SetText(std::to_wstring((int)data));
	}
}

void BulletUIComponent::Serialize(nlohmann::json& j) const
{
}

void BulletUIComponent::Deserialize(const nlohmann::json& j)
{
}
