#pragma once
#include "Component.h"
#include "IEventListener.h"

class TransformComponent;

class FlyingObstacleComponent : public Component
{
public:
	static constexpr const char* StaticTypeName = "FlyingObstacleComponent";
	virtual const char* GetTypeName() const override { return StaticTypeName; }

	FlyingObstacleComponent();

	void Start();

	virtual ~FlyingObstacleComponent() = default;

	virtual void Update(float deltaTime) override;// 추후 더 추가할 업데이트

	virtual void OnEvent(EventType type, const void* data);

	virtual void Serialize(nlohmann::json& j) const override;
	virtual void Deserialize(const nlohmann::json& j) override;

private:	
	TransformComponent* m_TransformComponent;

	float m_Z = 0;

	float m_MaxFallingSpeed = 1500;
	float m_FallingSpeed = 0;
	float m_Delay = 0;

	bool isDone = false;
};

