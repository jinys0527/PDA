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
		m_EventDispatcher.RemoveListener(EventType::KeyDown, m_Controller);
		m_EventDispatcher.RemoveListener(EventType::KeyUp, m_Controller);
	}

	virtual void Update(float deltaTime);// ���� �⺻ ���� ������Ʈ�� �ٸ��� ����
	virtual void Render(std::vector<RenderInfo>& renderInfo);// �Ƹ� �׸��� ��� ������ ���� �ٲ��, �׸��ڸ� �� Ŭ���� �ٱ��� ������Ʈ�� �Ѵٸ� �׳� ������ �� �� ���� �� Ŭ���� �ȿ� �ΰ� �ȴٸ� ���⼭ ���� �׸��� ��

	RunPlayerController* m_Controller;
	RigidbodyComponent* m_RigidbodyComponent;// Ȥ�� ���� ���� �����͵� ��� Ŀ�� �� ������ ������ �˴ϴ�

	FSM& GetFSM() { return m_Fsm; }

	bool GetIsGround() { return isGround; }
	void SetIsGround(bool value) { isGround = value; }

	float GetRailHeight() { return m_RailHeight; }


	void SetZ(float value) { m_Z = value; }
	float GetZ() { return m_Z; }

	bool GetSlide() { return isSlide; }

	void SetSlide(bool value) { isSlide = value; }

protected:

	FSM m_Fsm;

	bool isGround = false;

	bool isSlide = false;

	float m_RailHeight = 200;

	float m_KickCool = 0;

	float m_SlideCool = 0;

	//float m_SprayCool = 0;

	float m_Z = 0;
};

