#pragma once
#include "GameObject.h"
#include "RunPlayerController.h"
#include "RigidbodyComponent.h"
#include "FSM.h"
#include <iostream>

//class RunPlayerController;

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

	float GetInvincibleTime() { return m_InvincibleTime; }

	int GetHp() { return m_Hp; }
	
	void SetHp(int value) { m_Hp = value; }

	bool GetIsFlip() { return m_IsFlip; }

	void SetIsFlip(bool value) { m_IsFlip = value; }

protected:

	FSM m_Fsm;

	bool m_IsGround = false;

	bool m_IsSlide = false;

	bool m_IsFlip = false;

	float m_RailHeight = 200;

	float m_KickCool = 0;

	float m_SlideCool = 0;

	//float m_SprayCool = 0;

	float m_InvincibleTime = 0;

	float m_Z = 0;

	int m_Hp = 3;

	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_ShadowBitmap;
};

