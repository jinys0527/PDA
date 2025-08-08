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
	Math::Vector2F delta = { 3000, 550 };
	m_TransformComponent->SetPosition(delta);
}

void DroneComponent::Update(float deltaTime)
{

	Math::Vector2F delta = { 0, 0 };

	delta.x = -deltaTime * 1000;


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
