#pragma once
#include "Component.h"
#include "CameraObject.h"

class CameraComponent : public Component
{
	friend class CameraObject;
public:
	CameraComponent() = default;
	CameraComponent(const float width, const float height);
	virtual ~CameraComponent() = default;
	static constexpr const char* StaticTypeName = "CameraComponent";
	const char* GetTypeName() const override { return StaticTypeName; }

	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;

	D2D1::Matrix3x2F GetViewMatrix();
	
protected:
	float m_Width;
	float m_Height;

	float m_Zoom = 1;
};

REGISTER_COMPONENT(CameraComponent);