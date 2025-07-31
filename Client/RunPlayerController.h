#pragma once

#include "Component.h"
#include "GameObject.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"

// 뛰는 씬의 플레이어를 조종할 컴포넌트
class RunPlayerController : public Component, public IEventListener
{
public:
	static constexpr const char* StaticTypeName = "RunPlayerController";
	virtual const char* GetTypeName() const override { return StaticTypeName; }

	RunPlayerController() : Component() , IEventListener()
	{
		m_Z = 0;
		m_Velocity = 0;
	}

	virtual ~RunPlayerController()
	{
		// 아직 없음
	}

	void OnEvent(EventType type, const void* data) override;// 입력 받을 곳
	virtual void Update(float deltaTime) override;// 추후 더 추가할 업데이트


	virtual void Serialize(nlohmann::json& j) const override;
	virtual void Deserialize(const nlohmann::json& j) override;

	float GetZ()
	{
		return m_Z;
	}

private:
	// 입력 처리
	bool m_IsWPressed = false;
	bool m_IsAPressed = false;
	bool m_IsSPressed = false;
	bool m_IsDPressed = false;
	bool m_IsSpacePressed = false;
	bool m_IsShiftPressed = false;

	bool m_IsJump = false;
	bool m_IsSlide = false;

	bool m_IsJumpStart = false;

	RigidbodyComponent* m_RigidBodyComponent;
	TransformComponent* m_TransformComponent;

	float m_Z;
	float m_Velocity;
	float m_JumpPower = 10.0f;
	float m_Gravity = 20;
	float m_JumpCancelSpeed = 10.0f;
};

