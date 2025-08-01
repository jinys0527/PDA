#pragma once
#include "GameObject.h"
#include "RunPlayerController.h"
#include "RigidbodyComponent.h"
#include "FSM.h"

//class RunPlayerController;

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

		m_RigidbodyComponent->SetGravity(Math::Vector2F(0, -20));

		{
			{

				State idleState{
					[this]() 
					{
						std::cout << "idle ����" << std::endl;
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
					[]() { std::cout << "idle ����" << std::endl; }
				};

				m_Fsm.AddState("Idle", idleState);
			}
			{
				State kickState{
					[this]() 
					{
						std::cout << "kick ����" << std::endl;
						this->GetFSM().Trigger("Idle");// ���߿� �ִϸ��̼��� ���� �ɶ� �ִϸ��̼� �� �������̶�� Ż���� �������̴�
					},
					[](float dt) {},
					[]() { std::cout << "kick ����" << std::endl; }
				};

				m_Fsm.AddState("Kick", kickState);
			}
			{
				State jumpUpState{
					[]() {std::cout << "jumpUp ����" << std::endl; },
					[this](float dt) {
						if (this->GetComponent<RigidbodyComponent>()->GetVelocity().y < -3)
							this->GetFSM().Trigger("JumpDown");
						else if (this->GetComponent<RigidbodyComponent>()->GetVelocity().y < 3)
							this->GetFSM().Trigger("JumpPose");
						else if(this->isGround)
							this->GetFSM().Trigger("Idle");
					},
					[]() { std::cout << "jumpUp ����" << std::endl; }
				};

				m_Fsm.AddState("JumpUp", jumpUpState);
			}
			{
				State jumpPoseState{
					[]() {std::cout << "jumpPose ����" << std::endl; },
					[this](float dt) 
					{
						if (this->GetComponent<RigidbodyComponent>()->GetVelocity().y < -3)
							this->GetFSM().Trigger("JumpDown");
						else if (this->isGround)
							this->GetFSM().Trigger("Idle");
					},
					[]() { std::cout << "jumpPose ����" << std::endl; }
				};

				m_Fsm.AddState("JumpPose", jumpPoseState);
			}
			{
				State jumpDownState{
					[]() {std::cout << "jumpDown ����" << std::endl; },
					[this](float dt) 
					{
						if (this->isGround)
							this->GetFSM().Trigger("Idle");
					},
					[]() { std::cout << "jumpDown ����" << std::endl; }
				};

				m_Fsm.AddState("JumpDown", jumpDownState);
			}
			{
				State slideState{
					[this]() 
					{
						std::cout << "slide ����" << std::endl; 
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
						std::cout << "slide ����" << std::endl; 
						this->SetSlide(false);
					}
				};
				m_Fsm.AddState("Slide", slideState);
			}
			{
				State sprayState{
					[]() {std::cout << "spray ����" << std::endl; },
					[this](float dt) 
					{
						static float time = 0; // ���߿� �ִϸ��̼��� ���� �ɶ� �ִϸ��̼� �� �������̶�� Ż���� �������̴�
						time += dt;
						if (time >= 3)
						{
							time = 0;
							this->GetFSM().Trigger("Idle");
						}
					},
					[]() { std::cout << "spray ����" << std::endl; } // �����ϸ鼭 ���� ������ isJump ������ �� ����
				};
				m_Fsm.AddState("Spray", sprayState);
			}
			{
				State hurtState{
					[]() {std::cout << "hurt ����" << std::endl; },
					[this](float dt)
					{
											static float time = 0; // ���߿� �ִϸ��̼��� ���� �ɶ� �ִϸ��̼� �� �������̶�� Ż���� �������̴�
						time += dt;
						if (time >= 3)
						{
							time = 0;
							this->GetFSM().Trigger("Idle");
						}
					},
					[]() { std::cout << "hurt ����" << std::endl; }
				};
				m_Fsm.AddState("Hurt", hurtState);
			}
			{
				State deathState{
					[]() {std::cout << "death ����" << std::endl; },
					[](float dt) {},
					[]() { std::cout << "death ����" << std::endl; }
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

