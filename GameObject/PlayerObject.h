#pragma once
#include "GameObject.h"
#include "RunPlayerController.h"
#include "RigidbodyComponent.h"
#include "FSM.h"
#include <iostream>

//class RunPlayerController;

//존재 이유 플레이어 생성마다 수많은 FSM 컴포넌트의 상태 설정과, 컴포넌트 생성을 씬에서 하기엔 힘들것 같아 생성시 동시에 컴포넌트를 내부에서 처리하게함
class PlayerObject : public GameObject
{
public:
	PlayerObject(EventDispatcher& eventDispatcher);
	
	~PlayerObject()
	{
		// 이벤트 제거
		for (auto it = m_Components.begin(); it != m_Components.end(); it++)
		{
			//getcomponent
		}
	}

	virtual void Update(float deltaTime);// 아직 기본 게임 오브젝트랑 다를게 없음
	virtual void Render(std::vector<RenderInfo>& renderInfo);// 아마 그림자 어떻게 할지에 따라 바뀔듯, 그림자를 이 클래스 바깥의 오브젝트로 한다면 그냥 렌더가 될 것 같고 이 클래스 안에 두게 된다면 여기서 같이 그리게 함

	RunPlayerController* m_Controller;
	RigidbodyComponent* m_RigidbodyComponent;// 혹시 몰라 쓰는 포인터들 비용 커질 것 같으면 지워도 됩니다

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

