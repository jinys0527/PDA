#include "pch.h"
#include "PlayerObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "UIImageComponent.h"

void PlayerObject::Update(float deltaTime)
{
	//static float time = 0;

	//time += deltaTime;

	//if (time >= 1.0f)
	//{
	//	time -= 1.0f;
	//	SpriteRenderer* sprite = GetComponent<SpriteRenderer>();

	//	//if (&it != nullptr)
	//	//{
	//		sprite->SetFlipX(!sprite->GetFlipX());
	//	//}
	//}

	GameObject::Update(deltaTime);
}

void PlayerObject::Render(std::vector<RenderInfo>& renderInfo)
{
	auto sprite = GetComponent<SpriteRenderer>();
	auto image = GetComponent<UIImageComponent>();

	if (sprite)
	{
		RenderInfo info;
		info.bitmap = sprite->GetTexture();
		info.worldMatrix = m_Transform->GetWorldMatrix() * D2D1::Matrix3x2F::Translation(0, GetComponent<RunPlayerController>()->GetZ());
		info.size = { 1,1 };
		if (sprite->GetFlipX())
			info.size = { -1, 1 };
		info.pivot = sprite->GetPivot();
		// UI가 아닌 일반 오브젝트 위치로 설정
		info.anchor = Anchor{ {0.0f, 0.0f}, {0.0f, 0.0f} }; // (0,0)-(0,0) 고정값
		info.anchoredPosition = m_Transform->GetPosition();
		info.sizeDelta = { 0, 0 };
		info.parentSize = { 0, 0 };
		renderInfo.push_back(info);
		
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
