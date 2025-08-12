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

void Background::Render(std::vector<RenderInfo>& renderInfo)
{
	for (auto& spriteRenderer : GetComponents<SpriteRenderer>())
	{
		RenderInfo info;
		info.bitmap = spriteRenderer->GetTexture();
		D2D1::Matrix3x2F size = D2D1::Matrix3x2F::Identity();
		size._11 = 0.5f;
		size._22 = 0.5f;
		info.worldMatrix = size * m_Transform->GetWorldMatrix();
		info.pivot = spriteRenderer->GetPivot();
		// Opacity 적용
		info.opacity = spriteRenderer->GetOpacity();
		// UI가 아닌 일반 오브젝트 위치로 설정
		info.useSrcRect = spriteRenderer->GetUseSrcRect();
		info.srcRect = spriteRenderer->GetSrcRect();
		renderInfo.emplace_back(info);
	}
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
