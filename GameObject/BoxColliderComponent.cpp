#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <iostream>

void BoxColliderComponent::Start()
{
	GetEventDispatcher().AddListener(EventType::CollisionEnter, this);
	GetEventDispatcher().AddListener(EventType::CollisionStay, this);
	GetEventDispatcher().AddListener(EventType::CollisionExit, this);
	auto* transform = m_Owner->GetComponent<TransformComponent>();
	if (transform)
	{
		m_Center = transform->GetPosition();
	}
}

bool BoxColliderComponent::BoxVsBox(const BoxColliderComponent& other) const
{
    Vec2F thisMin = m_Center - m_Size / 2;
    Vec2F thisMax = m_Center + m_Size / 2;;
    Vec2F otherMin = other.m_Center - other.m_Size / 2;
    Vec2F otherMax = other.m_Center + other.m_Size / 2;

    return (thisMax.x >= otherMin.x && thisMin.x <= otherMax.x) &&
           (thisMax.y >= otherMin.y && thisMin.y <= otherMax.y);
}

void BoxColliderComponent::Serialize(nlohmann::json& j) const
{
}

void BoxColliderComponent::Deserialize(const nlohmann::json& j)
{
}

void BoxColliderComponent::Update(float deltaTime)
{
	auto* transform = m_Owner->GetComponent<TransformComponent>();
	if (transform)
	{
		m_Center = transform->GetPosition();
	}

	m_CurrentCollisions.clear();


}

void BoxColliderComponent::OnEvent(EventType type, const void* data)
{
	switch (type)
	{
	case EventType::CollisionEnter:
		OnCollisionEnter(static_cast<const CollisionInfo*>(data));
		break;
	case EventType::CollisionStay:
		OnCollisionStay(static_cast<const CollisionInfo*>(data));
		break;
	case EventType::CollisionExit:
		OnCollisionExit(static_cast<const CollisionInfo*>(data));
		break;
	}
}

void BoxColliderComponent::OnDestroy()
{
	GetEventDispatcher().RemoveListener(EventType::CollisionEnter, this);
	GetEventDispatcher().RemoveListener(EventType::CollisionStay, this);
	GetEventDispatcher().RemoveListener(EventType::CollisionExit, this);
}
