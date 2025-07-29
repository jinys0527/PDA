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
		auto it = m_Components.find(typeid(SpriteRenderer));

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
	auto it = m_Components.find(typeid(SpriteRenderer));// 아직 기존과 동일 아마 그림자 그리는 것 추후에 추가할 듯
	auto it2 = m_Components.find(typeid(UIImageComponent));

	if (it != m_Components.end())
	{
		SpriteRenderer* sprite = dynamic_cast<SpriteRenderer*>(it->second.get());
		if (sprite)
		{
			RenderInfo info;
			info.bitmap = sprite->GetTexture();
			info.position = m_Transform->GetPosition();
			info.scale = m_Transform->GetScale();
			info.parentSize.x = 0;
			info.parentSize.y = 0;
			info.sizeDelta.x = 0;
			info.sizeDelta.y = 0;
			info.anchoredPosition.x = 0;
			info.anchoredPosition.y = 0;
			//if (sprite->GetFlipX())
			//	info.scale.x = -info.scale.x;
			//if (sprite->GetFlipY())
			//	info.scale.y = -info.scale.y;
			info.rotation = m_Transform->GetRotation();
			info.pivot = sprite->GetPivot();
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
