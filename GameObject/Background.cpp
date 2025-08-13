#include "Background.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "CameraObject.h"
#include "CameraComponent.h"

void Background::Update(float deltaTime)
{
	if (m_isScroll)
	{
		Scroll(deltaTime);
	}

	TransformComponent* trans = GetComponent<TransformComponent>();
	float x = trans->GetPosition().x;

	int xSize = GetComponent<SpriteRenderer>()->GetTexture()->GetSize().width;

	if (x < -xSize)
	{
		trans->SetPosition({ x + xSize * 2, trans->GetPosition().y });
	}

	__super::Update(deltaTime);
}

void Background::Update(float deltaTime, const CameraObject* camera)
{
	__super::Update(deltaTime);

	TransformComponent* trans = GetComponent<TransformComponent>();
	float x = trans->GetPosition().x;
	int xSize = GetComponent<SpriteRenderer>()->GetTexture()->GetSize().width;

	// 카메라 위치 + 화면 절반 크기 가져오기
	auto cameraComp = camera->GetComponent<CameraComponent>();
	auto cameraPos = camera->GetComponent<TransformComponent>()->GetPosition();
	float cameraWidth = cameraComp->GetWidth() / cameraComp->GetZoom();
	float cameraLeft = cameraPos.x - cameraWidth * 0.5f;

	// 배경이 왼쪽 화면 범위를 벗어났을 때 뒤로 보내기
	if (x + xSize < cameraLeft)
	{
		trans->SetPosition({ x + xSize * 2, trans->GetPosition().y });
	}
}

void Background::FixedUpdate()
{
}

void Background::Scroll(float deltaTime)
{
	if (!m_isScroll)
	{
		return;
	}
	TransformComponent* trans = GetComponent<TransformComponent>();
	Math::Vector2F pos = trans->GetPosition();
	trans->SetPosition({ pos.x - m_moveSpeed * deltaTime, pos.y });
}
