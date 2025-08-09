#include "BulletUIComponent.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "UITextComponent.h"

BulletUIComponent::~BulletUIComponent()
{
	GetEventDispatcher().RemoveListener(EventType::OnPlayerReinforcedBulletChanged, this);
}

void BulletUIComponent::Start()
{
	GetEventDispatcher().AddListener(EventType::OnPlayerReinforcedBulletChanged, this);
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
