#include "FlyingObstacleComponent.h"
#include "Obstacle.h"
#include "TransformComponent.h"


FlyingObstacleComponent::FlyingObstacleComponent()
{

}

void FlyingObstacleComponent::Start()
{
	m_TransformComponent = m_Owner->GetComponent<TransformComponent>();
	Math::Vector2F delta = { 3000, 500 };
	m_TransformComponent->SetPosition(delta);
}

void FlyingObstacleComponent::Update(float deltaTime)
{
	if (isDone)
		return;
	Math::Vector2F delta = { 0, 0 };
	if (m_TransformComponent->GetPosition().x >= 1500)
	{
		delta.x = -deltaTime * 1000;
	}
	else if(m_TransformComponent->GetPosition().y >= -500)
	{
		m_FallingSpeed += 10;
		if (m_FallingSpeed >= m_MaxFallingSpeed)
			m_FallingSpeed = m_MaxFallingSpeed;
		delta.y = -deltaTime * m_FallingSpeed;
	}
	else
	{
		m_TransformComponent->DetachFromParent();
		isDone = true;
	}

	m_Owner->GetComponent<TransformComponent>()->Translate(delta);
}

void FlyingObstacleComponent::OnEvent(EventType type, const void* data)
{
}

void FlyingObstacleComponent::Serialize(nlohmann::json& j) const
{
}

void FlyingObstacleComponent::Deserialize(const nlohmann::json& j)
{
}
