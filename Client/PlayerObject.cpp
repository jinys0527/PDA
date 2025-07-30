#include "pch.h"
#include "PlayerObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "UIImageComponent.h"

void PlayerObject::Update(float deltaTime)
{
	static float time = 0;

	time += deltaTime;

	if (time >= 1.0f)
	{
		time -= 1.0f;
		auto it = m_Components.find(SpriteRenderer::StaticTypeName);

		//if (&it != nullptr)
		//{
			SpriteRenderer* sprite = dynamic_cast<SpriteRenderer*>(it->second.get());
			sprite->SetFlipX(!sprite->GetFlipX());
		//}
	}

	for (auto it = m_Components.begin(); it != m_Components.end(); it++)// 기존과 동일
	{
		it->second->Update(deltaTime);
	}
}

void PlayerObject::Render(std::vector<RenderInfo>& renderInfo)
{
	auto it = m_Components.find(SpriteRenderer::StaticTypeName);
	auto it2 = m_Components.find(UIImageComponent::StaticTypeName);

	if (it != m_Components.end())
	{
		SpriteRenderer* sprite = dynamic_cast<SpriteRenderer*>(it->second.get());
		if (sprite)
		{
			RenderInfo info;
			info.bitmap = sprite->GetTexture();
			info.worldMatrix = m_Transform->GetWorldMatrix() * D2D1::Matrix3x2F::Translation(0, dynamic_cast<RunPlayerController*>(m_Components.find(RunPlayerController::StaticTypeName)->second.get())->GetZ());
			info.pivot = sprite->GetPivot();
			// UI가 아닌 일반 오브젝트 위치로 설정
			info.anchor = Anchor{ {0.0f, 0.0f}, {0.0f, 0.0f} }; // (0,0)-(0,0) 고정값
			info.anchoredPosition = m_Transform->GetPosition();
			info.sizeDelta = { 0, 0 };
			info.parentSize = { 0, 0 };
			renderInfo.push_back(info);
		}
	}
	else if (it2 != m_Components.end())
	{
		UIImageComponent* image = dynamic_cast<UIImageComponent*>(it2->second.get());
		if (image)
		{
			RenderInfo info;
			renderInfo.push_back(info);
		}
	}
	else
	{
		return;
	}
}
