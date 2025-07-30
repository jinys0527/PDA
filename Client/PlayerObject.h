#pragma once
#include "GameObject.h"
#include "RunPlayerController.h"
#include "RigidbodyComponent.h"
#include "FSM.h"


//���� ���� �÷��̾� �������� ������ FSM ������Ʈ�� ���� ������, ������Ʈ ������ ������ �ϱ⿣ ����� ���� ������ ���ÿ� ������Ʈ�� ���ο��� ó���ϰ���
class PlayerObject : public GameObject
{
public:
	PlayerObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher) 
	{
		m_Controller = AddComponent<RunPlayerController>();// �÷��̾� ���� ������Ʈ �߰�
		eventDispatcher.AddListener(EventType::KeyDown, m_Controller);// �̺�Ʈ �߰�
		eventDispatcher.AddListener(EventType::KeyUp, m_Controller);
		m_RigidbodyComponent = AddComponent<RigidbodyComponent>();
		m_RigidbodyComponent->Start();
		//m_FSMComponent = AddComponent<FSMComponent>();
		m_FSM = std::make_unique<FSM>();
	}
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
	//FSMComponent* m_FSMComponent;
	std::unique_ptr<FSM> m_FSM;
};

