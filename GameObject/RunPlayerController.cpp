#include "pch.h"
#include "RunPlayerController.h"
#include "PlayerObject.h"
#include "Event.h"

RunPlayerController::RunPlayerController() : Component(), IEventListener()
{
	m_Z = 0;
	m_Velocity = 0;

	//m_PlayerOwner = (PlayerObject*)(m_Owner);

	m_RailHeight = 200;


}


void RunPlayerController::Update(float deltaTime)
{
	// Transform ������Ʈ�� �ִ� �����̴� �Լ� ��� ������ �� 

	if (m_RigidBodyComponent == nullptr)
	{
		m_RigidBodyComponent = m_Owner->GetComponent<RigidbodyComponent>();
		m_TransformComponent = m_Owner->GetComponent<TransformComponent>();
		if (m_RigidBodyComponent == nullptr || m_TransformComponent == nullptr)
		{
			return;
		}
	}
	if (m_PlayerOwner == nullptr)
	{
		m_PlayerOwner = (PlayerObject*)(m_Owner);
		m_RailHeight = m_PlayerOwner->GetRailHeight();
	}

	m_Z = m_PlayerOwner->GetZ();

	float prevZ = m_PlayerOwner->GetZ();

	Math::Vector2F delta = MoveCheck(deltaTime);
	
	JumpCheck();

	SlideCheck();

	m_RigidBodyComponent->Integrate(deltaTime);

	Math::Vector2F pos = m_TransformComponent->GetPosition();
	pos.y -= prevZ * m_RailHeight;

	if (pos.y <= 0 && m_RigidBodyComponent->GetVelocity().y < 0) // ���� 
	{
		pos.y = 0;
		Math::Vector2F vel = m_RigidBodyComponent->GetVelocity();
		vel.y = 0;
		m_RigidBodyComponent->SetVelocity(vel);
		//m_RigidBodyComponent->SetVelocity(Math::Vector2F(0, 0));
		m_IsJump = false;
		m_PlayerOwner->SetIsGround(true);
	}

	pos.y += m_Z * m_RailHeight;
	m_TransformComponent->SetPosition(pos);




	//{		//���� ���� y�� z�� ����
	//	if (m_IsSlide)
	//	{
	//		delta.y = -50;
	//	}
	//	else
	//	{
	//		delta.y = 1;
	//	}

	//	if (m_IsJump)
	//		delta.y = m_Z;


	//}

	if (delta.x != 0 || delta.y != 0)
	{
		m_Owner->GetComponent<TransformComponent>()->Translate(delta);// ������ �̰� ����ؿ�
		//m_Owner->GetComponent<TransformComponent>()->SetPosition(delta);// ���� ����(z�� �� �Ǵ��� y�� ���°�)
	}

	m_PlayerOwner->SetZ(m_Z);

	//m_Position.x += delta.x;
	//m_Position.y += delta.y;
}


void RunPlayerController::OnEvent(EventType type, const void* data)
{
	// Ű �Է� ó��

	if (type == EventType::KeyDown)
	{
		auto keyData = static_cast<const Events::KeyEvent*>(data);
		if (!keyData) return;

		bool isDown = (type == EventType::KeyDown);

		switch (keyData->key)
		{
		case 'W': m_IsWPressedDown = isDown; m_IsWPressed = isDown; break;
		case 'A': m_IsAPressed = isDown; break;
		case 'S': m_IsSPressedDown = isDown; m_IsSPressed = isDown; break;
		case 'D': m_IsDPressed = isDown; break;
		case 'P':
		{
			m_Hp -= 1; 
			if (m_Hp > 0)
				m_PlayerOwner->GetFSM().ChangeState("Hurt");
			else
				m_PlayerOwner->GetFSM().ChangeState("Death");
		}
		break;
		case VK_SPACE : m_IsSpacePressed = isDown; break;
		case VK_SHIFT : m_IsShiftPressed = isDown; break;
		default: break;
		}
	}
	else
	{
		auto keyData = static_cast<const Events::KeyEvent*>(data);
		if (!keyData) return;

		bool isDown = (type == EventType::KeyDown);

		switch (keyData->key)
		{
		case 'W': m_IsWPressed = isDown; m_RailMoveCool = 0; break;
		case 'A': m_IsAPressed = isDown; break;
		case 'S': m_IsSPressed = isDown; m_RailMoveCool = 0; break;
		case 'D': m_IsDPressed = isDown; break;
		case VK_SPACE : m_IsSpacePressed = isDown; break;
		case VK_SHIFT : m_IsShiftPressed = isDown; break;
		default: break;
		}
	}
}

void RunPlayerController::Serialize(nlohmann::json& j) const
{
}

void RunPlayerController::Deserialize(const nlohmann::json& j)
{
}

Math::Vector2F RunPlayerController::MoveCheck(float deltaTime)
{
	Math::Vector2F delta = { 0.0f, 0.0f };

	constexpr float moveSpeed = 500.0f; // �ʴ� �̵� �ӵ�

	if (m_IsWPressed && m_RailMoveDown == false && m_RailMoveUp == false) m_RailMoveCool += deltaTime;
	if (m_IsAPressed) delta.x -= moveSpeed * deltaTime;
	if (m_IsSPressed && m_RailMoveDown == false && m_RailMoveUp == false) m_RailMoveCool -= deltaTime;
	if (m_IsDPressed) delta.x += moveSpeed * deltaTime;

	if (m_RailMoveCool >= 0.15f)// Ȧ�� 0.15�� ���� ���� �ٲ�
	{
		m_RailMoveCool = 0;
		m_IsWPressedDown = true;
	}
	else if (m_RailMoveCool <= -0.15f)
	{
		m_RailMoveCool = 0;
		m_IsSPressedDown = true;
	}

	m_Z = Math::Clamp(m_Z, m_minZ, m_maxZ);
	if (m_Z == m_minZ)
	{
		m_IsSPressedDown = false;
		m_RailTargetZ = Math::Clamp(m_RailTargetZ, m_minZ, m_maxZ);;
	}
	else if (m_Z == m_maxZ)
	{
		m_IsWPressedDown = false;
		m_RailTargetZ = Math::Clamp(m_RailTargetZ, m_minZ, m_maxZ);;
	}

	if (m_IsWPressedDown)
	{
		m_RailTargetZ += 1;
		m_RailMoveUp = true;
		m_IsWPressedDown = false;
	}
	if (m_IsSPressedDown)
	{
		m_RailTargetZ -= 1;
		m_RailMoveDown = true;
		m_IsSPressedDown = false;
	}

	//if (m_RailMoveUp)

	//if (m_RailMoveDown)

	if (m_RailMoveUp && m_RailMoveDown)
	{
		if (m_Z >= m_RailTargetZ)
		{
			m_RailMoveUp = false;
		}
		else
		{
			m_RailMoveDown = false;
		}
	}



	if (m_RailMoveUp)
	{
		m_Z += deltaTime * 10;
		if (m_Z >= m_RailTargetZ)
		{
			m_RailMoveUp = false;
			m_Z = m_RailTargetZ;
		}
	}
	else if (m_RailMoveDown)
	{
		m_Z -= deltaTime * 10;
		if (m_Z <= m_RailTargetZ)
		{
			m_RailMoveDown = false;
			m_Z = m_RailTargetZ;
		}
	}

	return delta;
}

void RunPlayerController::JumpCheck()
{
	if (m_IsSpacePressed && m_IsShiftPressed == false)
	{
		if (m_IsJump == false)
		{
			m_IsJumpStart = true;
			m_IsJump = true;
		}
	}

	if (m_IsJumpStart)
	{
		//Math::Vector2F jumpPower = { 0, m_JumpPower };
		//Math::Vector2F jumpPower = { 0, 100 };
		//m_RigidBodyComponent->AddForce(jumpPower);// ���߿� ������ ���� �����
		m_RigidBodyComponent->SetVelocity(Math::Vector2F(0.0f, m_JumpPower));
		m_IsJumpStart = false;
		m_IsSlide = false;
		m_PlayerOwner->GetFSM().Trigger("JumpUp");
		m_PlayerOwner->SetIsGround(false);
	}
}

void RunPlayerController::SlideCheck()
{
	if (m_IsJump)
	{
		if (m_IsShiftPressed)
		{
			//m_Velocity = -5.0f;// ���߿� JumpCancelSpeed ���� �����
			m_RigidBodyComponent->SetVelocity(Math::Vector2F(0.0f, -m_JumpCancelSpeed));
		}
	}
	else
	{
		if (m_IsShiftPressed)
		{
			//m_IsSlide = true; // �ٴڿ��� shift �ϸ� ��ũ��
			m_PlayerOwner->GetFSM().Trigger("Slide");
		}
		//else
		//{
		//	m_IsSlide = false;
		//}
	}
}
