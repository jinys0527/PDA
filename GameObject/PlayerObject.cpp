#include "pch.h"
#include "PlayerObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "UIImageComponent.h"
#include "BoxColliderComponent.h"
#include "AnimationComponent.h"

PlayerObject::PlayerObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	m_Controller = AddComponent<RunPlayerController>();// �÷��̾� ���� ������Ʈ �߰�
	m_Controller->Start();
	m_RigidbodyComponent = AddComponent<RigidbodyComponent>();
	m_RigidbodyComponent->Start();
	m_RigidbodyComponent->SetGravity(Math::Vector2F(0, -20));

	AddComponent<BoxColliderComponent>()->SetSize(Vec2F(100, 100));
	GetComponent<BoxColliderComponent>()->Start();

	//AddComponent<AnimationComponent>()->AddClip("Idle");

	{ // �� ���� �� �̰ɷ� �ݾ��ֽñ�
		{
			State idleState{
				[this]()
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("run");
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "idle ����" << std::endl;
					this->m_KickCool = 0;
					if (!m_Controller->GetIsBoss())
					{
						m_Fsm.Trigger("Run");
					}
				},
				[this](float dt)
				{
					if (m_Controller->GetIsMoving())
						m_Fsm.Trigger("Run");
				},
				[]() { std::cout << "idle ����" << std::endl; }
			};

			m_Fsm.AddState("Idle", idleState);
		}
		{
			State runState{
				[this]()
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("run");
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "run ����" << std::endl;
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

					if (m_Controller->GetIsBoss()&&!m_Controller->GetIsMoving())
						m_Fsm.Trigger("Idle");
				},
				[]() { std::cout << "run ����" << std::endl; }
			};

			m_Fsm.AddState("Run", runState);
		}
		{
			State kickState{
				[this]()
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("kickground", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "kick ����" << std::endl;
					//this->GetFSM().Trigger("Idle");// ���߿� �ִϸ��̼��� ���� �ɶ� �ִϸ��̼� �� �������̶�� Ż���� �������̴�
				},
				[this](float dt) 
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						if (anim->IsAnimationFinished())
						{
							//anim->Play("attack");
							this->GetFSM().Trigger("Idle");
						}
					}
				},
				[]() { std::cout << "kick ����" << std::endl; }
			};

			m_Fsm.AddState("Kick", kickState);
		}
		{
			State jumpUpState{
				[this]() 
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("jumpup", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "jumpUp ����" << std::endl; 
				},
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
				[this]() 
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("jumptop", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "jumpPose ����" << std::endl; 
				},
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
				[this]() 
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("jumpdown", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "jumpDown ����" << std::endl; 
				},
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
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("slide");
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "slide ����" << std::endl;
					this->SetSlide(true);

					this->m_SlideDuration = 0;
				},
				[this](float dt)
				{
					this->m_SlideDuration += dt;
					if (this->m_SlideDuration >= 1)
					{
						this->GetFSM().Trigger("Idle");
						this->m_SlideCool = 2;
					}
				},
				[this]()
				{
					this->m_SlideDuration = 0;
					std::cout << "slide ����" << std::endl;
					this->SetSlide(false);
				}
			};
			m_Fsm.AddState("Slide", slideState);
		}
		{
			State waitingSprayState{
					[this]()
					{
						auto anim = this->GetComponent<AnimationComponent>();
						if (anim)
						{
							anim->Play("run", true);
							auto sr = this->GetComponent<SpriteRenderer>();
							sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
							sr->SetTextureKey("boss");
						}
						this->m_HoldingAttack = 0;
						std::cout << "waitSpray ����" << std::endl;
					},
					[this](float dt)
					{
					if(this->m_Controller->GetIsHoldingAttack())
						this->m_HoldingAttack += dt;
						if(m_HoldingAttack >= 1 && this->m_Controller->GetIsBoss())
							this->GetFSM().Trigger("ReadySpray");
						else if (m_HoldingAttack >= 10)
							this->GetFSM().Trigger("Shoot");
					},
					[this]() 
					{ 
						std::cout << "waitSpray ����" << std::endl; 
					} // �����ϸ鼭 ���� ������ isJump ������ �� ����
			};
			m_Fsm.AddState("WaitSpray", waitingSprayState);
		}
		{
			State sprayState{
				[this]() 
				{
					std::cout << "spray ����" << std::endl;
					PlayerAttackInfo info;
					info.damage = 1;
					info.mousePos = m_Controller->GetMousePos();
					info.player = this;
					this->m_EventDispatcher.Dispatch(EventType::OnPlayerAttack, static_cast<const void*>(&info));
					if (!m_IsAttackSuccessed)
					{
						m_Fsm.Trigger("FailSpray");
						return;
					}
					m_IsAttackSuccessed = false;
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("attack", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
				},
				[this](float dt)
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						if (anim->IsAnimationFinished())
						{
							//anim->Play("attack");
							this->GetFSM().Trigger("SuccessSpray");
						}
					}
				},
				[]() { std::cout << "spray ����" << std::endl; } // �����ϸ鼭 ���� ������ isJump ������ �� ����
			};
			m_Fsm.AddState("Spray", sprayState);
		}
		{
			State readySprayState{
					[this]()
					{
						auto anim = this->GetComponent<AnimationComponent>();
						if (anim)
						{
							anim->Play("charge", true);
							auto sr = this->GetComponent<SpriteRenderer>();
							sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
							sr->SetTextureKey("boss");
						}
						std::cout << "sprayReady ����" << std::endl;
					},
					[this](float dt)
					{
						//auto anim = this->GetComponent<AnimationComponent>();
						//if (anim)
						//{
						//	if (anim->IsAnimationFinished())
						//	{
						//		anim->Play("attack");
						//		this->GetFSM().Trigger("Idle");
						//	}
						//}
						if (this->m_Controller->GetIsHoldingAttack())
						this->m_HoldingAttack += dt;
						if (m_HoldingAttack >= 10)
							this->GetFSM().Trigger("Shoot");
					},
					[this]() 
					{ 
						std::cout << "sprayReady ����" << std::endl;
					} // �����ϸ鼭 ���� ������ isJump ������ �� ����
			};
			m_Fsm.AddState("ReadySpray", readySprayState);
		}
		{
			State StrongSprayState{
				[this]()
				{
					std::cout << "strongSpray ����" << std::endl;
					PlayerAttackInfo info;
					info.damage = 1;
					info.mousePos = m_Controller->GetMousePos();
					info.player = this;
					this->m_EventDispatcher.Dispatch(EventType::OnPlayerAttack, static_cast<const void*>(&info));
					if (!m_IsAttackSuccessed)
					{
						m_Fsm.Trigger("FailSpray");
						return;
					}
					m_IsAttackSuccessed = false;
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("chargeshot", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
				},
				[this](float dt)
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						if (anim->IsAnimationFinished())
						{
							//anim->Play("attack");
							this->GetFSM().Trigger("SuccessSpray");
						}
					}
				},
				[]() { std::cout << "strongSpray ����" << std::endl; } // �����ϸ鼭 ���� ������ isJump ������ �� ����
			};
			m_Fsm.AddState("StrongSpray", StrongSprayState);
		}
		{
			State FailSprayState{
				[this]()
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("markingfail", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "failSpray ����" << std::endl;
				},
				[this](float dt)
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						if (anim->IsAnimationFinished())
						{
							//anim->Play("attack");
							this->GetFSM().Trigger("Idle");
						}
					}
				},
				[]() { std::cout << "failSpray ����" << std::endl; } // �����ϸ鼭 ���� ������ isJump ������ �� ����
			};
			m_Fsm.AddState("FailSpray", FailSprayState);
		}
		{
			State SuccessSprayState{
				[this]()
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("markingsuccess", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "successSpray ����" << std::endl;
				},
				[this](float dt)
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						if (anim->IsAnimationFinished())
						{
							//anim->Play("attack");
							this->GetFSM().Trigger("Idle");
						}
					}
				},
				[]() { std::cout << "successSpray ����" << std::endl; } // �����ϸ鼭 ���� ������ isJump ������ �� ����
			};
			m_Fsm.AddState("SuccessSpray", SuccessSprayState);
		}
		{
			State hurtState{
				[this]() 
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("hitted", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "hurt ����" << std::endl; 
					this->m_InvincibleTime = 3.0f;
				},
				[this](float dt)
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						if (anim->IsAnimationFinished())
						{
							//anim->Play("attack");
							this->GetFSM().Trigger("Idle");
						}
					}
				},
				[]() { std::cout << "hurt ����" << std::endl; }
			};
			m_Fsm.AddState("Hurt", hurtState);
		}
		{
			State deathState{
				[this]() 
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("dead", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "death ����" << std::endl; 
				},
				[](float dt) {},
				[]() { std::cout << "death ����" << std::endl; }
			};
			m_Fsm.AddState("Death", deathState);
		}
		{
			m_Fsm.AddTransition("Idle", "Kick", "Kick");// Idle Kick
			m_Fsm.AddTransition("Kick", "Idle", "Idle");// Kick Idle
			m_Fsm.AddTransition("Idle", "Run", "Run");// Idle Kick
			m_Fsm.AddTransition("Run", "Idle", "Idle");// Idle Kick
			m_Fsm.AddTransition("Run", "Kick", "Kick");// Idle Kick
			m_Fsm.AddTransition("Kick", "Run", "Run");// Idle Kick
			m_Fsm.AddTransition("Idle", "Slide", "Slide");// Idle Slide
			m_Fsm.AddTransition("Slide", "Idle", "Idle");// Slide Idle
			m_Fsm.AddTransition("Run", "Slide", "Slide");// Idle Slide
			m_Fsm.AddTransition("Kick", "Slide", "Slide");// Kick Slide
			m_Fsm.AddTransition("Idle", "WaitSpray", "WaitSpray");// Idle Spray
			m_Fsm.AddTransition("Run", "WaitSpray", "WaitSpray");// Idle Spray
			m_Fsm.AddTransition("Kick", "WaitSpray", "WaitSpray");// Kick Spray
			m_Fsm.AddTransition("WaitSpray", "Spray", "Shoot");// Kick Spray
			m_Fsm.AddTransition("WaitSpray", "ReadySpray", "ReadySpray");// Kick Spray
			m_Fsm.AddTransition("ReadySpray", "StrongSpray", "Shoot");// Kick Spray
			m_Fsm.AddTransition("Spray", "SuccessSpray", "SuccessSpray");// Spray Idle
			m_Fsm.AddTransition("StrongSpray", "SuccessSpray", "SuccessSpray");// Spray Idle
			m_Fsm.AddTransition("Spray", "FailSpray", "FailSpray");// Spray Idle
			m_Fsm.AddTransition("StrongSpray", "FailSpray", "FailSpray");// Spray Idle
			m_Fsm.AddTransition("FailSpray", "Idle", "Idle");// Spray Idle
			m_Fsm.AddTransition("SuccessSpray", "Idle", "Idle");// Spray Idle
			m_Fsm.AddTransition("Idle", "JumpUp", "JumpUp");// Idle JumpUp
			m_Fsm.AddTransition("Run", "JumpUp", "JumpUp");// Idle JumpUp
			m_Fsm.AddTransition("Kick", "JumpUp", "JumpUp");// Kick JumpUp
			m_Fsm.AddTransition("Slide", "JumpUp", "JumpUp");// Slide JumpUp
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
	else
		m_InvincibleTime = 0;

	if (m_SlideCool > 0)
		m_SlideCool -= deltaTime;
	else
		m_SlideCool = 0;

	GameObject::Update(deltaTime);

	m_Fsm.Update(deltaTime);
}

void PlayerObject::Render(std::vector<RenderInfo>& renderInfo)
{
	auto sprite = GetComponent<SpriteRenderer>();

	if (sprite)
	{
		{
			RenderInfo info;
			info.bitmap = m_ShadowBitmap;
			Math::Vector2F pos = m_Transform->GetPosition();
			float y = pos.y;
			pos.y = m_Z * m_RailHeight + 65.f;
			m_Transform->SetPosition(pos);
			info.size = { 1,1 };
			D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Identity();
			trans._22 = 0.7f;
			trans._32 = 15.0f;
			info.worldMatrix = trans * m_Transform->GetWorldMatrix();

			info.pivot = { m_ShadowBitmap.Get()->GetSize().width * 0.5f, m_ShadowBitmap.Get()->GetSize().height * 0.5f }; // �ٲپ� ����
			// UI�� �ƴ� �Ϲ� ������Ʈ ��ġ�� ����
			//float opacity = sprite->GetTexture().Get()->GetSize().height / (y + 1);
			float forSin = (y - m_Z * m_RailHeight) / (sprite->GetTexture().Get()->GetSize().height);
			forSin = forSin > asin(1) ? asin(1) : forSin;
			float opacity = sin(forSin);
			info.opacity = 1.0f - opacity;
			renderInfo.push_back(info);
			pos.y = y;
			m_Transform->SetPosition(pos);
		}
		{
			RenderInfo info;
			info.bitmap = sprite->GetTexture();
			D2D1::Matrix3x2F flip = D2D1::Matrix3x2F::Identity();
			if(m_IsFlip)
				flip.m11 = -1;
			info.worldMatrix = flip * m_Transform->GetWorldMatrix(); // D2D1::Matrix3x2F::Translation(0, z * m_RailHeight) *  
			info.size = { 1,1 };
			D2D1_SIZE_F size;
			size.width = sprite->GetSrcRect().right - sprite->GetSrcRect().left;
			size.height = sprite->GetSrcRect().bottom - sprite->GetSrcRect().top;
			sprite->SetPivotPreset(SpritePivotPreset::BottomCenter, size);

			info.pivot = sprite->GetPivot(); // �ٲپ� ����
			// UI�� �ƴ� �Ϲ� ������Ʈ ��ġ�� ����
			float opacity = abs(cos(m_InvincibleTime * 5));
			info.opacity = opacity;
			info.useSrcRect = sprite->GetUseSrcRect();
			info.srcRect = sprite->GetSrcRect();
			renderInfo.push_back(info);
		}
	}

}

void PlayerObject::SetShadowBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> shadow)
{
	m_ShadowBitmap = shadow;
}

void PlayerObject::SetHp(int value)
{
	m_Hp = value; 
	GetEventDispatcher().Dispatch(EventType::OnPlayerHpChanged, (const void*)value);// ���� hp�� ����}
}

void PlayerObject::SetBullet(int value)
{
	m_ReinforcedBullet = value; 
	GetEventDispatcher().Dispatch(EventType::OnPlayerReinforcedBulletChanged, (const void*)value);
}

void PlayerObject::SetCameraObject(GameObject* cameraObject)
{

	m_CameraObject = cameraObject;

}

GameObject* PlayerObject::GetCameraObject()
{
	return m_CameraObject;
}
