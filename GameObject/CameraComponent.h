#pragma once
#include "Component.h"
#include "CameraObject.h"

class CameraComponent : public Component
{
	friend class CameraObject;
public:
	virtual ~CameraComponent() = default;
	std::string GetTypeName() override { return "CameraComponent"; }
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;
protected:
	float m_Width;
	float m_Height;
};

