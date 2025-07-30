#include "pch.h"
#include "RunPlayerController.h"
#include "Event.h"


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

	constexpr float moveSpeed = 500.0f; // �ʴ� �̵� �ӵ�
	Math::Vector2F delta = { 0.0f, 0.0f };

	if (m_IsWPressed) m_Z += moveSpeed * deltaTime;
	if (m_IsAPressed) delta.x -= moveSpeed * deltaTime;
	if (m_IsSPressed) m_Z -= moveSpeed * deltaTime;
	if (m_IsDPressed) delta.x += moveSpeed * deltaTime;

	if (m_IsSpacePressed && m_IsSlide == false)
	{
		if (m_IsJump == false)
		{
			m_IsJumpStart = true;
			m_IsJump = true;
		}
	}

	//m_Velocity -= 0.1f;
	Math::Vector2F fallSpeed = { 0, -m_Gravity };
	//m_RigidBodyComponent->AddForce(fallSpeed);
	m_RigidBodyComponent->SetGravity(fallSpeed);

	if (m_IsJumpStart)
	{
		//Math::Vector2F jumpPower = { 0, m_JumpPower };
		//Math::Vector2F jumpPower = { 0, 100 };
		//m_RigidBodyComponent->AddForce(jumpPower);// ���߿� ������ ���� �����
		m_RigidBodyComponent->SetVelocity(Math::Vector2F(0.0f, m_JumpPower));
		m_IsJumpStart = false;
		m_IsSlide = false;
	}

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
			m_IsSlide = true; // �ٴڿ��� shift �ϸ� ��ũ��
		}
		else
		{
			m_IsSlide = false;
		}
	}

	m_RigidBodyComponent->Integrate(deltaTime);

	//delta += m_RigidBodyComponent->GetVelocity();// ���߿� gravity ���� �����

	Math::Vector2F pos = m_TransformComponent->GetPosition();

	if (pos.y <= 0 && m_RigidBodyComponent->GetVelocity().y < 0) // ���� 
	{
		pos.y = 0;
		m_TransformComponent->SetPosition(pos);
		//delta.y = 0;
		pos = m_RigidBodyComponent->GetVelocity();// pos ��Ȱ������ �ӵ� ���
		pos.y = 0;
		m_RigidBodyComponent->SetVelocity(pos);
		//m_RigidBodyComponent->SetVelocity(Math::Vector2F(0, 0));
		m_IsJump = false;
	}

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
		case 'W': m_IsWPressed = isDown; break;
		case 'A': m_IsAPressed = isDown; break;
		case 'S': m_IsSPressed = isDown; break;
		case 'D': m_IsDPressed = isDown; break;
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
		case 'W': m_IsWPressed = isDown; break;
		case 'A': m_IsAPressed = isDown; break;
		case 'S': m_IsSPressed = isDown; break;
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
