#pragma once
#include "GameObject.h"
#include "RunPlayerController.h"
#include "RigidbodyComponent.h"
#include "FSM.h"
#include <iostream>

//class RunPlayerController;

struct PlayerAttackInfo
{
	int damage;
	PlayerObject* player;
	Math::Vector2F mousePos;
};

//���� ���� �÷��̾� �������� ������ FSM ������Ʈ�� ���� ������, ������Ʈ ������ ������ �ϱ⿣ ����� ���� ������ ���ÿ� ������Ʈ�� ���ο��� ó���ϰ���
class PlayerObject : public GameObject
{
public:
	PlayerObject(EventDispatcher& eventDispatcher);
	
	~PlayerObject()
	{
		// �̺�Ʈ ����
		for (auto it = m_Components.begin(); it != m_Components.end(); it++)
		{
			//getcomponent
		}
	}

	virtual void Update(float deltaTime);// ���� �⺻ ���� ������Ʈ�� �ٸ��� ����
	virtual void Render(std::vector<RenderInfo>& renderInfo);// �Ƹ� �׸��� ��� ������ ���� �ٲ��, �׸��ڸ� �� Ŭ���� �ٱ��� ������Ʈ�� �Ѵٸ� �׳� ������ �� �� ���� �� Ŭ���� �ȿ� �ΰ� �ȴٸ� ���⼭ ���� �׸��� ��

	RunPlayerController* m_Controller;
	RigidbodyComponent* m_RigidbodyComponent;// Ȥ�� ���� ���� �����͵� ��� Ŀ�� �� ������ ������ �˴ϴ�

	FSM& GetFSM() { return m_Fsm; }

	bool GetIsGround() { return m_IsGround; }
	void SetIsGround(bool value) { m_IsGround = value; }

	float GetRailHeight() { return m_RailHeight; }

	void SetShadowBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> shadow);

	void SetZ(float value) { m_Z = value; }
	float GetZ() { return m_Z; }

	bool GetSlide() { return m_IsSlide; }

	void SetSlide(bool value) { m_IsSlide = value; }

	float GetSlideCool() { return m_SlideCool; }
	void SetSlideCool(float value) { m_SlideCool = value; }

	float GetSlideDuration() { return m_SlideDuration; }
	void SetSlideDuration(float value) { m_SlideDuration = value; }

	float GetInvincibleTime() { return m_InvincibleTime; }

	int GetHp() { return m_Hp; }
	
	void SetHp(int value);

	bool GetIsFlip() { return m_IsFlip; }

	void SetIsFlip(bool value) { m_IsFlip = value; }

	void SetBullet(int value);

	int GetBullet() { return m_ReinforcedBullet; }

	void SetIsAttackSuccessed(bool value) { if(value) m_IsAttackSuccessed = value; }

	void SetCameraObject(GameObject* cameraObject);
	
	GameObject* GetCameraObject();

	void SetScene(bool value) { m_IsScene = value; }

	bool GetScene() { return m_IsScene; }

protected:

	FSM m_Fsm;

	bool m_IsGround = false;

	bool m_IsSlide = false;

	bool m_IsFlip = false;

	bool m_IsAttackSuccessed = false;

	float m_RailHeight = 108.f;

	float m_KickCool = 0;

	float m_SlideCool = 0;

	float m_SlideDuration = 0;

	//float m_SprayCool = 0;

	float m_InvincibleTime = 0;

	float m_Z = 0;

	int m_Hp = 5;

	float m_HoldingAttack = 0;

	int m_ReinforcedBullet = 0;

	bool m_IsScene = false;

	int m_Layer = 0;

	GameObject* m_CameraObject;

	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_ShadowBitmap;
};

