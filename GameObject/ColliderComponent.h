#pragma once
#include "Component.h"
#include "SimpleMathHelper.h"
#include <unordered_set>
#include "FSM.h"

using Vec2F = Math::Vector2F;

class ColliderComponent;

struct CollisionInfo
{
	ColliderComponent* self;         // �ڽ�
	ColliderComponent* other;        // �浹 ���
	Vec2F normal;                    // �浹 ��� (self ����)
	Vec2F contactPoint;              // ���� ���� (�ʿ��� ���)
	float penetrationDepth;          // ħ�� ���� (�и� ��꿡 ���)
};

class GameObject;

class ColliderComponent : public Component, public IEventListener
{
	using CollisionCallback = std::function<void(const CollisionInfo&)>;
public:
	static constexpr const char* StaticTypeName = "ColliderComponent";
	const char* GetTypeName() const override { return StaticTypeName; }

	ColliderComponent();
	virtual ~ColliderComponent() { OnDestroy(); }

	virtual void Start();

	void SetCenter(const Vec2F& center)
	{
		m_Center = center;
	}
	const Vec2F& GetCenter() const {
		return m_Center;
	}

	void SetOnEnter(CollisionCallback cb) { m_OnEnter = cb; }
	void SetOnStay(CollisionCallback cb) { m_OnStay = cb; }
	void SetOnExit(CollisionCallback cb) { m_OnExit = cb; }
	void SetOnTrigger(CollisionCallback cb) { m_OnTrigger = cb; }

	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
	virtual void OnDestroy();

	FSM& GetFSM() { return m_Fsm; }

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;
protected:
	void OnCollisionEnter(const CollisionInfo* info)	{ if (m_OnEnter) m_OnEnter(*info); }
	void OnCollisionStay(const CollisionInfo* info)		{ if (m_OnStay) m_OnStay(*info); }
	void OnCollisionExit(const CollisionInfo* info)		{ if (m_OnExit) m_OnExit(*info); }
	void OnCollisionTrigger(const CollisionInfo* info)	{ if (m_OnTrigger) m_OnTrigger(*info); }

	CollisionCallback m_OnEnter = nullptr;
	CollisionCallback m_OnStay = nullptr;
	CollisionCallback m_OnExit = nullptr;
	CollisionCallback m_OnTrigger = nullptr;

	bool m_IsTrigger;
	Vec2F m_Center;
	FSM m_Fsm;

	std::unordered_set<GameObject*> m_CurrentCollisions;
};

REGISTER_COMPONENT(ColliderComponent);