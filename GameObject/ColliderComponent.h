#pragma once
#include "Component.h"
#include "SimpleMathHelper.h"
#include <unordered_set>

using Vec2F = Math::Vector2F;

class ColliderComponent;

enum class CollisionState
{
	None,
	Enter,
	Stay,
	Exit
};

struct CollisionInfo
{
	ColliderComponent* self;         // 자신
	ColliderComponent* other;        // 충돌 상대
	Vec2F normal;                    // 충돌 노멀 (self 기준)
	Vec2F contactPoint;              // 접촉 지점 (필요할 경우)
	float penetrationDepth;          // 침투 깊이 (분리 계산에 사용)
};

class GameObject;

class ColliderComponent : public Component, public IEventListener
{
	
public:
	virtual ~ColliderComponent() { OnDestroy(); }
	virtual void Start();
	void SetCenter(const Vec2F& center)
	{
		m_Center = center;
	}
	const Vec2F& GetCenter() const {
		return m_Center;
	}
	std::string GetTypeName() override { return "ColliderComponent"; }
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
	virtual void OnDestroy();
	CollisionState GetCollisionState() const { return m_CollisionState; }
	void SetCollisionState(CollisionState state) { m_CollisionState = state; }

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;
protected:
	virtual void OnCollisionEnter(const CollisionInfo* info) {}
	virtual void OnCollisionStay(const CollisionInfo* info)  {}
	virtual void OnCollisionExit(const CollisionInfo* info)  {}



	bool m_IsTrigger;
	Vec2F m_Center;

	std::unordered_set<GameObject*> m_CurrentCollisions;
	CollisionState m_CollisionState = CollisionState::None;
};

