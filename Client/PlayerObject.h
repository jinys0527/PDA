#pragma once
#include "GameObject.h"
#include "RunPlayerController.h"
#include "RigidbodyComponent.h"
#include "FSM.h"

//class RunPlayerController;

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

		m_RigidbodyComponent->SetGravity(Math::Vector2F(0, -20));

		{
			{

				State idleState{
					[this]() 
					{
						std::cout << "idle 들어옴" << std::endl;
						this->m_KickCool = 0;
					},
					[this](float dt) 
					{
						this->m_KickCool += dt;
						if (this->m_KickCool >= 2.0f)
						{
							this->m_KickCool = 0;
							this->GetFSM().Trigger("Kick");
						}
					},
					[]() { std::cout << "idle 나감" << std::endl; }
				};

				m_Fsm.AddState("Idle", idleState);
			}
			{
				State kickState{
					[this]() 
					{
						std::cout << "kick 들어옴" << std::endl;
						this->GetFSM().Trigger("Idle");// 나중에 애니메이션을 쓰게 될때 애니메이션 끝 프레임이라면 탈출을 넣을것이다
					},
					[](float dt) {},
					[]() { std::cout << "kick 나감" << std::endl; }
				};

				m_Fsm.AddState("Kick", kickState);
			}
			{
				State jumpUpState{
					[]() {std::cout << "jumpUp 들어옴" << std::endl; },
					[this](float dt) {
						if (this->GetComponent<RigidbodyComponent>()->GetVelocity().y < -3)
							this->GetFSM().Trigger("JumpDown");
						else if (this->GetComponent<RigidbodyComponent>()->GetVelocity().y < 3)
							this->GetFSM().Trigger("JumpPose");
						else if(this->isGround)
							this->GetFSM().Trigger("Idle");
					},
					[]() { std::cout << "jumpUp 나감" << std::endl; }
				};

				m_Fsm.AddState("JumpUp", jumpUpState);
			}
			{
				State jumpPoseState{
					[]() {std::cout << "jumpPose 들어옴" << std::endl; },
					[this](float dt) 
					{
						if (this->GetComponent<RigidbodyComponent>()->GetVelocity().y < -3)
							this->GetFSM().Trigger("JumpDown");
						else if (this->isGround)
							this->GetFSM().Trigger("Idle");
					},
					[]() { std::cout << "jumpPose 나감" << std::endl; }
				};

				m_Fsm.AddState("JumpPose", jumpPoseState);
			}
			{
				State jumpDownState{
					[]() {std::cout << "jumpDown 들어옴" << std::endl; },
					[this](float dt) 
					{
						if (this->isGround)
							this->GetFSM().Trigger("Idle");
					},
					[]() { std::cout << "jumpDown 나감" << std::endl; }
				};

				m_Fsm.AddState("JumpDown", jumpDownState);
			}
			{
				State slideState{
					[this]() 
					{
						std::cout << "slide 들어옴" << std::endl; 
						this->SetSlide(true);
					},
					[this](float dt) 
					{
						static float time = 0;
						time += dt;
						if (time >= 3)
						{
							time = 0;
							this->GetFSM().Trigger("Idle");
						}
					},
					[this]() 
					{ 
						std::cout << "slide 나감" << std::endl; 
						this->SetSlide(false);
					}
				};
				m_Fsm.AddState("Slide", slideState);
			}
			{
				State sprayState{
					[]() {std::cout << "spray 들어옴" << std::endl; },
					[this](float dt) 
					{
						static float time = 0; // 나중에 애니메이션을 쓰게 될때 애니메이션 끝 프레임이라면 탈출을 넣을것이다
						time += dt;
						if (time >= 3)
						{
							time = 0;
							this->GetFSM().Trigger("Idle");
						}
					},
					[]() { std::cout << "spray 나감" << std::endl; } // 착지하면서 공격 끝나면 isJump 꺼지게 할 예정
				};
				m_Fsm.AddState("Spray", sprayState);
			}
			{
				State hurtState{
					[]() {std::cout << "hurt 들어옴" << std::endl; },
					[this](float dt)
					{
											static float time = 0; // 나중에 애니메이션을 쓰게 될때 애니메이션 끝 프레임이라면 탈출을 넣을것이다
						time += dt;
						if (time >= 3)
						{
							time = 0;
							this->GetFSM().Trigger("Idle");
						}
					},
					[]() { std::cout << "hurt 나감" << std::endl; }
				};
				m_Fsm.AddState("Hurt", hurtState);
			}
			{
				State deathState{
					[]() {std::cout << "death 들어옴" << std::endl; },
					[](float dt) {},
					[]() { std::cout << "death 나감" << std::endl; }
				};
				m_Fsm.AddState("Death", deathState);
			}
			{
				m_Fsm.AddTransition("Idle", "Kick", "Kick");// Idle Kick
				m_Fsm.AddTransition("Kick", "Idle", "Idle");// Kick Idle
				m_Fsm.AddTransition("Idle", "Slide", "Slide");// Idle Slide
				m_Fsm.AddTransition("Slide", "Idle", "Idle");// Slide Idle
				m_Fsm.AddTransition("Kick", "Slide", "Slide");// Kick Slide
				m_Fsm.AddTransition("Idle", "Spray", "Spray");// Idle Spray
				m_Fsm.AddTransition("Spray", "Idle", "Idle");// Spray Idle
				m_Fsm.AddTransition("Kick", "Spray", "Spray");// Kick Spray
				m_Fsm.AddTransition("Spray", "Slide", "Slide");// Spray Slide
				m_Fsm.AddTransition("Idle", "JumpUp", "JumpUp");// Idle JumpUp
				m_Fsm.AddTransition("Kick", "JumpUp", "JumpUp");// Kick JumpUp
				m_Fsm.AddTransition("Slide", "JumpUp", "JumpUp");// Slide JumpUp
				m_Fsm.AddTransition("Spray", "JumpUp", "JumpUp");// Spray JumpUp
				m_Fsm.AddTransition("JumpUp", "JumpPose", "JumpPose");// JumpUp JumpPose
				m_Fsm.AddTransition("JumpUp", "JumpDown", "JumpDown");// JumpUp JumpDown
				m_Fsm.AddTransition("JumpPose", "JumpDown", "JumpDown");// JumpPose JumpDown
				m_Fsm.AddTransition("JumpUp", "Idle", "Idle");// JumpUp Idle
				m_Fsm.AddTransition("JumpPose", "Idle", "Idle");// JumpPose Idle
				m_Fsm.AddTransition("JumpDown", "Idle", "Idle");// JumpDown Idle
				m_Fsm.AddTransition("Hurt", "Idle", "Idle");// Hurt Idle


				m_Fsm.SetInitialState("Idle");
			}
		}
		
		//m_Fsm.AddState();
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

	FSM& GetFSM() { return m_Fsm; }

	bool GetIsGround() { return isGround; }
	void SetIsGround(bool value) { isGround = value; }

	float GetRailHeight() { return m_RailHeight; }

	float GetZ() { return m_Z; }

	void SetZ(float value) { m_Z = value; }

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

