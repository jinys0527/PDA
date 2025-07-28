#include "pch.h"
#include "RunPlayerController.h"
#include "TransformComponent.h"
#include "Event.h"


void RunPlayerController::Update(float deltaTime)
{
	// Transform ������Ʈ�� �ִ� �����̴� �Լ� ��� ������ �� 

	constexpr float moveSpeed = 100.0f; // �ʴ� �̵� �ӵ�
	Math::Vector2F delta = { 0.0f, 0.0f };

	if (m_IsWPressed) delta.y -= moveSpeed * deltaTime;
	if (m_IsAPressed) delta.x -= moveSpeed * deltaTime;
	if (m_IsSPressed) delta.y += moveSpeed * deltaTime;
	if (m_IsDPressed) delta.x += moveSpeed * deltaTime;

	if (delta.x != 0 || delta.y != 0)
	{
		m_Owner->GetComponent<TransformComponent>()->Translate(delta);
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
		default: break;
		}
	}
}

std::string RunPlayerController::GetTypeName()
{
	return "RunPlayerController";// ������Ʈ �̸� �ޱ�
}

void RunPlayerController::Serialize(nlohmann::json& j) const
{
}

void RunPlayerController::Deserialize(const nlohmann::json& j)
{
}
