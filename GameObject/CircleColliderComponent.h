#pragma once
#include "ColliderComponent.h"

class BoxColliderComponent;

class CircleColliderComponent : public ColliderComponent
{
public:
	virtual ~CircleColliderComponent() = default;
	bool CircleVsCircle(const CircleColliderComponent& other) const;
	bool CircleVsBox(const BoxColliderComponent& other) const;
	std::string GetTypeName() override { return "CircleColliderComponent"; }
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;
protected:
	float m_Radius;
};

