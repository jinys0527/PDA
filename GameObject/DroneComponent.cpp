#include "DroneComponent.h"
#include "GameObject.h"
#include "ItemObject.h"
#include "TransformComponent.h"

DroneComponent::DroneComponent()
{
}

void DroneComponent::Start()
{
	m_TransformComponent = m_Owner->GetComponent<TransformComponent>();
	Math::Vector2F delta = { 900, 200 };
	m_TransformComponent->SetPosition(delta);
}

void DroneComponent::Update(float deltaTime)
{
	if(!m_TransformComponent->GetParent())
		return;
	Math::Vector2F delta = { 0, 0 };


	if (m_TransformComponent->GetPosition().x >= 700)
	{
		delta.x = -deltaTime * 1000;
		m_Delay = 1;
	}
	else
	{
		m_Delay -= deltaTime;
		if(m_Delay <= 0)
			delta.x = -deltaTime * 1000;

		if (m_Owner->GetComponent<TransformComponent>()->GetPosition().x < -2000)
			m_Owner->GetComponent<TransformComponent>()->DetachFromParent();
	}

	m_Owner->GetComponent<TransformComponent>()->Translate(delta);
}

void DroneComponent::OnEvent(EventType type, const void* data)
{
}

void DroneComponent::Serialize(nlohmann::json& j) const
{
}

void DroneComponent::Deserialize(const nlohmann::json& j)
{
}
