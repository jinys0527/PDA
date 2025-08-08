#pragma once
#include "Component.h"
#include "IEventListener.h"

class TransformComponent;

class DroneComponent : public Component
{
public:
	static constexpr const char* StaticTypeName = "DroneComponent";
	virtual const char* GetTypeName() const override { return StaticTypeName; }

	DroneComponent();

	void Start();

	virtual ~DroneComponent() = default;

	virtual void Update(float deltaTime) override;// 추후 더 추가할 업데이트

	virtual void OnEvent(EventType type, const void* data);

	virtual void Serialize(nlohmann::json& j) const override;
	virtual void Deserialize(const nlohmann::json& j) override;

private:
	TransformComponent* m_TransformComponent;

};

