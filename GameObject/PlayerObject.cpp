#include "pch.h"
#include "PlayerObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "UIImageComponent.h"
#include "BoxColliderComponent.h"

PlayerObject::PlayerObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	m_Controller = AddComponent<RunPlayerController>();// �÷��̾� ���� ������Ʈ �߰�
	m_Controller->Start();
	m_RigidbodyComponent = AddComponent<RigidbodyComponent>();
	m_RigidbodyComponent->Start();
	m_RigidbodyComponent->SetGravity(Math::Vector2F(0, -20));

	AddComponent<BoxColliderComponent>()->SetSize(Vec2F(100, 100));
	GetComponent<BoxColliderComponent>()->Start();

	{ // �� ���� �� �̰ɷ� �ݾ��ֽñ�
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
					else if (this->m_IsGround)
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
					else if (this->m_IsGround)
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
					if (this->m_IsGround)
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
				[this]() {
					std::cout << "hurt ����" << std::endl; 
					this->m_InvincibleTime = 3.0f;
				},
				[this](float dt)
				{
					if (m_InvincibleTime <= 0)
					{
						m_InvincibleTime = 0;
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

void PlayerObject::Update(float deltaTime)
{
	//float temp = m_Transform->GetPosition().y;

	if (m_InvincibleTime > 0)
		m_InvincibleTime -= deltaTime;

	GameObject::Update(deltaTime);

	m_Fsm.Update(deltaTime);
}

void PlayerObject::Render(std::vector<RenderInfo>& renderInfo)
{
	auto sprite = GetComponent<SpriteRenderer>();
	auto image = GetComponent<UIImageComponent>();

	if (sprite)
	{
		{
			RenderInfo info;
			info.bitmap = sprite->GetTexture();
			D2D1::Matrix3x2F flip = D2D1::Matrix3x2F::Identity();
			if(m_IsFlip)
				flip.m11 = -1;
			info.worldMatrix = flip * m_Transform->GetWorldMatrix(); // D2D1::Matrix3x2F::Translation(0, z * m_RailHeight) *  
			info.size = { 1,1 };
			info.pivot = sprite->GetPivot(); // �ٲپ� ����
			// UI�� �ƴ� �Ϲ� ������Ʈ ��ġ�� ����
			renderInfo.push_back(info);
		}
		{
			RenderInfo info;
			info.bitmap = sprite->GetTexture();
			Math::Vector2F pos = m_Transform->GetPosition();
			float y = pos.y;
			pos.y = m_Z * m_RailHeight;
			m_Transform->SetPosition(pos);
			info.size = { 1,1 };
			D2D1::Matrix3x2F size = D2D1::Matrix3x2F::Identity();
			size._22 = 0.5f;
			info.worldMatrix = size * m_Transform->GetWorldMatrix();

			info.pivot = Math::Vector2F(180, 180);// ��� �ٲپ����
			// UI�� �ƴ� �Ϲ� ������Ʈ ��ġ�� ����
			//float opacity = sprite->GetTexture().Get()->GetSize().height / (y + 1);
			float forSin = (y - m_Z*m_RailHeight) / (sprite->GetTexture().Get()->GetSize().height);
			forSin = forSin > asin(1) ? asin(1) : forSin;
			float opacity = sin(forSin);
			info.opacity = 1.0f - opacity;
			renderInfo.push_back(info);
			pos.y = y;
			m_Transform->SetPosition(pos);
		}
	}
	else if (image)
	{
		RenderInfo info;
		renderInfo.push_back(info);
	}
	else
	{
		return;
	}
}
