#include "ColliderComponent.h"
#include "EventDispatcher.h"


void ColliderComponent::Start()
{
	GetEventDispatcher().AddListener(EventType::CollisionEnter, this);
	GetEventDispatcher().AddListener(EventType::CollisionStay, this);
	GetEventDispatcher().AddListener(EventType::CollisionExit, this);
}

void ColliderComponent::Update(float deltaTime)
{

}

void ColliderComponent::OnEvent(EventType type, const void* data)
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

void ColliderComponent::OnDestroy()
{
	GetEventDispatcher().RemoveListener(EventType::CollisionEnter, this);
	GetEventDispatcher().RemoveListener(EventType::CollisionStay, this);
	GetEventDispatcher().RemoveListener(EventType::CollisionExit, this);
}

void ColliderComponent::Serialize(nlohmann::json& j) const
{
}

void ColliderComponent::Deserialize(const nlohmann::json& j)
{
}
