#include "pch.h"
#include "PlayerObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "UIImageComponent.h"
#include "BoxColliderComponent.h"
#include "AnimationComponent.h"

PlayerObject::PlayerObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	m_Controller = AddComponent<RunPlayerController>();// 플레이어 조종 컴포넌트 추가
	m_Controller->Start();
	m_RigidbodyComponent = AddComponent<RigidbodyComponent>();
	m_RigidbodyComponent->Start();
	m_RigidbodyComponent->SetGravity(Math::Vector2F(0, -20));

	AddComponent<BoxColliderComponent>()->SetSize(Vec2F(100, 100));
	GetComponent<BoxColliderComponent>()->Start();

	//AddComponent<AnimationComponent>()->AddClip("Idle");

	{ // 좀 많이 길어서 이걸로 닫아주시길
		{
			State idleState{
				[this]()
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("attack");
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "idle 들어옴" << std::endl;
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
				[]() { std::cout << "idle 나감" << std::endl; }
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
						anim->Play("attack");
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "run 들어옴" << std::endl;
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
				[]() { std::cout << "run 나감" << std::endl; }
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
						anim->Play("attack", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "kick 들어옴" << std::endl;
					//this->GetFSM().Trigger("Idle");// 나중에 애니메이션을 쓰게 될때 애니메이션 끝 프레임이라면 탈출을 넣을것이다
				},
				[this](float dt) 
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						if (anim->IsAnimationFinished())
						{
							anim->Play("attack");
							this->GetFSM().Trigger("Idle");
						}
					}
				},
				[]() { std::cout << "kick 나감" << std::endl; }
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
						anim->Play("attack");
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "jumpUp 들어옴" << std::endl; 
				},
				[this](float dt) {
					if (this->GetComponent<RigidbodyComponent>()->GetVelocity().y < -3)
						this->GetFSM().Trigger("JumpDown");
					else if (this->GetComponent<RigidbodyComponent>()->GetVelocity().y < 3)
						this->GetFSM().Trigger("JumpPose");
					else if (this->m_IsGround)
						this->GetFSM().Trigger("Idle");
				},
				[]() { std::cout << "jumpUp 나감" << std::endl; }
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
						anim->Play("attack");
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "jumpPose 들어옴" << std::endl; 
				},
				[this](float dt)
				{
					if (this->GetComponent<RigidbodyComponent>()->GetVelocity().y < -3)
						this->GetFSM().Trigger("JumpDown");
					else if (this->m_IsGround)
						this->GetFSM().Trigger("Idle");
				},
				[]() { std::cout << "jumpPose 나감" << std::endl; }
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
						anim->Play("attack");
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "jumpDown 들어옴" << std::endl; 
				},
				[this](float dt)
				{
					if (this->m_IsGround)
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
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("attack");
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
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
			State waitingSprayState{
					[this]()
					{
						auto anim = this->GetComponent<AnimationComponent>();
						if (anim)
						{
							anim->Play("attack", true);
							auto sr = this->GetComponent<SpriteRenderer>();
							sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
							sr->SetTextureKey("boss");
						}
						std::cout << "sprayReady 들어옴" << std::endl;
					},
					[this](float dt)
					{
						auto anim = this->GetComponent<AnimationComponent>();
						if (anim)
						{
							if (anim->IsAnimationFinished())
							{
								anim->Play("attack");
								this->GetFSM().Trigger("Idle");
							}
						}
					},
					[]() { std::cout << "sprayReady 나감" << std::endl; } // 착지하면서 공격 끝나면 isJump 꺼지게 할 예정
			};
			m_Fsm.AddState("WaitSpray", waitingSprayState);
		}
		{
			State sprayState{
				[this]() 
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("attack", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "spray 들어옴" << std::endl; 
				},
				[this](float dt)
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						if (anim->IsAnimationFinished())
						{
							anim->Play("attack");
							this->GetFSM().Trigger("Idle");
						}
					}
				},
				[]() { std::cout << "spray 나감" << std::endl; } // 착지하면서 공격 끝나면 isJump 꺼지게 할 예정
			};
			m_Fsm.AddState("Spray", sprayState);
		}
		{
			State StrongSprayState{
				[this]()
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("attack", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "strongSpray 들어옴" << std::endl;
				},
				[this](float dt)
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						if (anim->IsAnimationFinished())
						{
							anim->Play("attack");
							this->GetFSM().Trigger("Idle");
						}
					}
				},
				[]() { std::cout << "strongSpray 나감" << std::endl; } // 착지하면서 공격 끝나면 isJump 꺼지게 할 예정
			};
			m_Fsm.AddState("StrongSpray", StrongSprayState);
		}
		{
			State hurtState{
				[this]() 
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						anim->Play("attack", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "hurt 들어옴" << std::endl; 
					this->m_InvincibleTime = 3.0f;
				},
				[this](float dt)
				{
					auto anim = this->GetComponent<AnimationComponent>();
					if (anim)
					{
						if (anim->IsAnimationFinished())
						{
							anim->Play("attack");
							this->GetFSM().Trigger("Idle");
						}
					}
				},
				[]() { std::cout << "hurt 나감" << std::endl; }
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
						anim->Play("attack", false);
						auto sr = this->GetComponent<SpriteRenderer>();
						sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
						sr->SetTextureKey("boss");
					}
					std::cout << "death 들어옴" << std::endl; 
				},
				[](float dt) {},
				[]() { std::cout << "death 나감" << std::endl; }
			};
			m_Fsm.AddState("Death", deathState);
		}
		{
			m_Fsm.AddTransition("Idle", "Kick", "Kick");// Idle Kick
			m_Fsm.AddTransition("Kick", "Idle", "Idle");// Kick Idle
			m_Fsm.AddTransition("Idle", "Run", "Run");// Idle Kick
			m_Fsm.AddTransition("Run", "Idle", "Idle");// Idle Kick
			m_Fsm.AddTransition("Idle", "Slide", "Slide");// Idle Slide
			m_Fsm.AddTransition("Slide", "Idle", "Idle");// Slide Idle
			m_Fsm.AddTransition("Run", "Slide", "Slide");// Idle Slide
			m_Fsm.AddTransition("Kick", "Slide", "Slide");// Kick Slide
			m_Fsm.AddTransition("Idle", "WaitSpray", "WaitSpray");// Idle Spray
			m_Fsm.AddTransition("Run", "WaitSpray", "WaitSpray");// Idle Spray
			m_Fsm.AddTransition("Kick", "WaitSpray", "WaitSpray");// Kick Spray
			m_Fsm.AddTransition("WaitSpray", "Spray", "Spray");// Kick Spray
			m_Fsm.AddTransition("WaitSpray", "StrongSpray", "StrongSpray");// Kick Spray
			m_Fsm.AddTransition("Spray", "Idle", "Idle");// Spray Idle
			m_Fsm.AddTransition("StrongSpray", "Idle", "Idle");// Spray Idle
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

			info.pivot = sprite->GetPivot(); // 바꾸어 놓음
			// UI가 아닌 일반 오브젝트 위치로 설정
			float opacity = abs(cos(m_InvincibleTime * 5));
			info.opacity = opacity;
			info.useSrcRect = sprite->GetUseSrcRect();
			info.srcRect = sprite->GetSrcRect();
			renderInfo.push_back(info);
		}
		{
			RenderInfo info;
			info.bitmap = m_ShadowBitmap;
			Math::Vector2F pos = m_Transform->GetPosition();
			float y = pos.y;
			pos.y = m_Z * m_RailHeight;
			m_Transform->SetPosition(pos);
			info.size = { 1,1 };
			D2D1::Matrix3x2F size = D2D1::Matrix3x2F::Identity();
			size._22 = 0.5f;
			info.worldMatrix = size * m_Transform->GetWorldMatrix();

			info.pivot = { m_ShadowBitmap.Get()->GetSize().width*0.5f, m_ShadowBitmap.Get()->GetSize().height*0.5f }; // 바꾸어 놓음
			// UI가 아닌 일반 오브젝트 위치로 설정
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

}

void PlayerObject::SetShadowBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> shadow)
{
	m_ShadowBitmap = shadow;
}
