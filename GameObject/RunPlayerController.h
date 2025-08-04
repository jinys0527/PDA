#pragma once

#include "Component.h"
#include "GameObject.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
//#include "PlayerObject.h"


class PlayerObject;

// �ٴ� ���� �÷��̾ ������ ������Ʈ
class RunPlayerController : public Component, public IEventListener
{
public:
	static constexpr const char* StaticTypeName = "RunPlayerController";
	virtual const char* GetTypeName() const override { return StaticTypeName; }

	RunPlayerController();

	virtual ~RunPlayerController()
	{
		// ���� ����
	}

	void OnEvent(EventType type, const void* data) override;// �Է� ���� ��
	virtual void Update(float deltaTime) override;// ���� �� �߰��� ������Ʈ


	virtual void Serialize(nlohmann::json& j) const override;
	virtual void Deserialize(const nlohmann::json& j) override;

	float GetZ()
	{
		return m_Z;
	}

private:

	Math::Vector2F MoveCheck(float deltaTime); // �ڵ� ���� ���̱� ����
	void JumpCheck();
	void SlideCheck();

	// �Է� ó��
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

	PlayerObject* m_PlayerOwner = nullptr; // ���� ���� �ҰŶ�

	float m_Z;
	float m_Velocity;
	float m_JumpPower = 10.0f;
	float m_JumpCancelSpeed = 10.0f;

	float m_RailHeight;

	int m_maxZ = 2;
	int m_minZ = 0;

	//Z���� ���� Y �� ����

	int m_Hp = 3;

};

