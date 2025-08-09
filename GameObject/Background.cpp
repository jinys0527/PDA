#include "Background.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"

void Background::Update(float deltaTime)
{
	Scroll(deltaTime);
	__super::Update(deltaTime);
	TransformComponent* trans = GetComponent<TransformComponent>();
	float x = trans->GetPosition().x;

	int xSize = GetComponent<SpriteRenderer>()->GetTexture()->GetSize().width;

	if (trans->GetPosition().x < -xSize)
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
