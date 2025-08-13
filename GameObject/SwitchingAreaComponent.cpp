#include "SwitchingAreaComponent.h"
#include "UIObject.h"
#include "RectTransformComponent.h"

#define switchingSpeed 250

void SwitchingAreaComponent::Start(int index)
{
	auto rect = m_Owner->GetComponent<RectTransformComponent>();
	rect->SetPosition({ 1920.0f * (index+1), 0.0f});
}

void SwitchingAreaComponent::Update(float deltaTime)
{
	if (m_RectTransComp == nullptr)
		m_RectTransComp = m_Owner->GetComponent<RectTransformComponent>();

	Math::Vector2F pos = m_RectTransComp->GetPosition();

	pos.x = pos.x - 960.0f + (m_RectTransComp->GetSize().x / 2.0f);
	pos.y = pos.y - 540.0f + (m_RectTransComp->GetSize().y / 2.0f);

	if (pos.x > -2000)
	{
		pos.x -= deltaTime * switchingSpeed;
	}

	if (pos.x < -2000)
	{
		pos.x = -2000;
	}

	m_RectTransComp->SetPosition(pos);
}

void SwitchingAreaComponent::OnEvent(EventType type, const void* data)
{
}

void SwitchingAreaComponent::Serialize(nlohmann::json& j) const
{
}

void SwitchingAreaComponent::Deserialize(const nlohmann::json& j)
{
}
