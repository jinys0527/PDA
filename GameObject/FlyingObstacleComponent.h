#pragma once
#include "Component.h"
#include "IEventListener.h"

class TransformComponent;
class Obstacle;

class FlyingObstacleComponent : public Component
{
public:
	static constexpr const char* StaticTypeName = "FlyingObstacleComponent";
	virtual const char* GetTypeName() const override { return StaticTypeName; }

	FlyingObstacleComponent();

	void Start();

	virtual ~FlyingObstacleComponent() = default;

	virtual void Update(float deltaTime) override;// ���� �� �߰��� ������Ʈ

	virtual void OnEvent(EventType type, const void* data);

	virtual void Serialize(nlohmann::json& j) const override;
	virtual void Deserialize(const nlohmann::json& j) override;

private:	
	TransformComponent* m_TransformComponent;
	float m_VirtualX = -100;
	float m_VirtualY = 400;

	float m_MaxFallingSpeed = 1500;
	float m_FallingSpeed = 0;

	bool isDone = false;
};

