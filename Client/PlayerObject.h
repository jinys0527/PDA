#pragma once
#include "GameObject.h"
#include "RunPlayerController.h"
#include "RigidbodyComponent.h"
#include "FSM.h"


//존재 이유 플레이어 생성마다 수많은 FSM 컴포넌트의 상태 설정과, 컴포넌트 생성을 씬에서 하기엔 힘들것 같아 생성시 동시에 컴포넌트를 내부에서 처리하게함
class PlayerObject : public GameObject
{
public:
	PlayerObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher) 
	{
		m_Controller = AddComponent<RunPlayerController>();// 플레이어 조종 컴포넌트 추가
		eventDispatcher.AddListener(EventType::KeyDown, m_Controller);// 이벤트 추가
		eventDispatcher.AddListener(EventType::KeyUp, m_Controller);
		m_RigidbodyComponent = AddComponent<RigidbodyComponent>();
		m_RigidbodyComponent->Start();
		//m_FSMComponent = AddComponent<FSMComponent>();
		m_FSM = std::make_unique<FSM>();
	}
	~PlayerObject()
	{
		// 이벤트 제거
		m_EventDispatcher.RemoveListener(EventType::KeyDown, m_Controller);
		m_EventDispatcher.RemoveListener(EventType::KeyUp, m_Controller);
	}

	virtual void Update(float deltaTime);// 아직 기본 게임 오브젝트랑 다를게 없음
	virtual void Render(std::vector<RenderInfo>& renderInfo);// 아마 그림자 어떻게 할지에 따라 바뀔듯, 그림자를 이 클래스 바깥의 오브젝트로 한다면 그냥 렌더가 될 것 같고 이 클래스 안에 두게 된다면 여기서 같이 그리게 함

	RunPlayerController* m_Controller;
	RigidbodyComponent* m_RigidbodyComponent;// 혹시 몰라 쓰는 포인터들 비용 커질 것 같으면 지워도 됩니다
	//FSMComponent* m_FSMComponent;
	std::unique_ptr<FSM> m_FSM;
};

