#include "FlyingObstacleComponent.h"
#include "Obstacle.h"
#include "ItemObject.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"


FlyingObstacleComponent::FlyingObstacleComponent()
{

}

void FlyingObstacleComponent::Start()
{
	m_TransformComponent = m_Owner->GetComponent<TransformComponent>();
	Math::Vector2F delta = { 3000, 200};
	m_TransformComponent->SetPosition(delta);
	if (dynamic_cast<Obstacle*>(m_Owner))
		m_Z = dynamic_cast<Obstacle*>(m_Owner)->GetZ();
	else if (dynamic_cast<ItemObject*>(m_Owner))
		m_Z = dynamic_cast<ItemObject*>(m_Owner)->GetZ();
}

void FlyingObstacleComponent::Update(float deltaTime)
{
	if (isDone)
		return;
	Math::Vector2F delta = { 0, 0 };
	if (m_TransformComponent->GetPosition().x >= 700)
	{
		delta.x = -deltaTime * 1000;
		m_Delay = 1;
	}
	else if(m_TransformComponent->GetPosition().y >= -540 + m_Z * 200)
	{
		m_Delay -= deltaTime;
		if (m_Delay <= 0)
		{
			m_FallingSpeed += 10;
			if (m_FallingSpeed >= m_MaxFallingSpeed)
				m_FallingSpeed = m_MaxFallingSpeed;
			delta.y = -deltaTime * m_FallingSpeed;
		}
	}
	else
	{
		m_TransformComponent->DetachFromParent();
		m_Owner->GetComponent<BoxColliderComponent>()->SetCenter(m_TransformComponent->GetPosition());
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
