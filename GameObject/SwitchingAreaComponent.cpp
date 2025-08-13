#include "SwitchingAreaComponent.h"
#include "UIObject.h"
#include "RectTransformComponent.h"

#define switchingSpeed 2500

void SwitchingAreaComponent::Start(int index)
{
	if (index > 1)
	{
		m_IsLoaded = true;
	}
	else
	{
		m_IsLoaded = false;
		m_IsStart = false;

		index = index % 2;

		if (index == 1)
		{
			m_IsStart = true;
		}

		auto rect = m_Owner->GetComponent<RectTransformComponent>();
		rect->SetPosition({ 1920.0f * (index + 1), 0.0f });
	}
}

void SwitchingAreaComponent::Update(float deltaTime)
{
	if (m_RectTransComp == nullptr)
		m_RectTransComp = m_Owner->GetComponent<RectTransformComponent>();

	Math::Vector2F pos = m_RectTransComp->GetPosition();

	pos.x = pos.x - 960.0f + (m_RectTransComp->GetSize().x / 2.0f);
	pos.y = pos.y - 540.0f + (m_RectTransComp->GetSize().y / 2.0f);

	if (m_IsStart)
	{
		pos.x -= 1900;
	}

	if (pos.x > -4000 && m_IsLoaded)
	{
		pos.x -= deltaTime * switchingSpeed;
	}
	else if (pos.x > -750)
	{
		pos.x -= deltaTime * switchingSpeed;
	}

	if (m_IsStart)
	{
		pos.x += 1900;
	}

	if (pos.x <= -4000 && m_IsLoaded)
	{
		pos.x = -4000;
		m_IsLoaded = false;
		m_IsStart = false;
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
