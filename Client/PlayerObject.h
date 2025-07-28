#pragma once
#include "GameObject.h"
#include "RunPlayerController.h"


//���� ���� �÷��̾� �������� ������ FSM ������Ʈ�� ���� ������, ������Ʈ ������ ������ �ϱ⿣ ����� ���� ������ ���ÿ� ������Ʈ�� ���ο��� ó���ϰ���
class PlayerObject : public GameObject
{
public:
	PlayerObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher) 
	{
		m_Controller = AddComponent<RunPlayerController>();// �÷��̾� ���� ������Ʈ �߰�
		eventDispatcher.AddListener(EventType::KeyDown, m_Controller);// �̺�Ʈ �߰�
		eventDispatcher.AddListener(EventType::KeyUp, m_Controller);
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
};

