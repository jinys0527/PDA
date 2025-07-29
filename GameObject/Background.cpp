#include "Background.h"
#include "TransformComponent.h"
void Background::Update(float deltaTime)
{
	Scroll(deltaTime);
	__super::Update(deltaTime);
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
