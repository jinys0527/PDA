#pragma once

#include "Component.h"
#include "GameObject.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
//#include "PlayerObject.h"


class PlayerObject;

// 뛰는 씬의 플레이어를 조종할 컴포넌트
class RunPlayerController : public Component, public IEventListener
{
public:
	static constexpr const char* StaticTypeName = "RunPlayerController";
	virtual const char* GetTypeName() const override { return StaticTypeName; }

	RunPlayerController();

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

	Math::Vector2F MoveCheck(float deltaTime); // 코드 길이 줄이기 위해
	void JumpCheck();
	void SlideCheck();

	// 입력 처리
	bool m_IsWPressed = false;
	bool m_IsWPressedDown = false;
	bool m_IsAPressed = false;
	bool m_IsSPressed = false;
	bool m_IsSPressedDown = false;
	bool m_IsDPressed = false;
	bool m_IsSpacePressed = false;
	bool m_IsShiftPressed = false;

	bool m_IsJump = false;
	bool m_IsSlide = false;

	bool m_IsJumpStart = false;

	bool m_RailMoveUp = false;
	bool m_RailMoveDown = false;

	float m_RailMoveCool = 0;
	float m_RailTargetZ = 0;

	RigidbodyComponent* m_RigidBodyComponent = nullptr;
	TransformComponent* m_TransformComponent = nullptr;

	PlayerObject* m_PlayerOwner = nullptr; // 많이 접근 할거라서

	float m_Z;
	float m_Velocity;
	float m_JumpPower = 10.0f;
	float m_JumpCancelSpeed = 10.0f;

	float m_RailHeight;

	int m_maxZ = 2;
	int m_minZ = 0;

	//Z축이 점프 Y 가 레인

	int m_Hp = 3;

};

