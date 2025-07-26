#pragma once
#include "ColliderComponent.h"
#include "SimpleMathHelper.h"
#include <iostream>

class BoxColliderComponent : public ColliderComponent
{
	using Vec2F = Math::Vector2F;
	friend class CircleColliderComponent;
public:
	virtual ~BoxColliderComponent() { OnDestroy(); }
	void Start() override;
	bool BoxVsBox(const BoxColliderComponent& other) const;
	void SetSize(const Vec2F& size) {
		m_Size = size;
	}

	const Vec2F& GetSize() const {
		return m_Size;
	}

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;

	std::string GetTypeName() override { return "BoxColliderComponent"; }
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
	void OnDestroy() override;
protected:
	Vec2F m_Size;
	void OnCollisionEnter(const CollisionInfo* info) override { std::cout << "enter" << std::endl; }
	void OnCollisionStay(const CollisionInfo* info) override { std::cout << "stay" << std::endl; }
	void OnCollisionExit(const CollisionInfo* info) override { std::cout << "exit" << std::endl; }
};

