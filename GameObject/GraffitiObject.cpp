#include "GraffitiObject.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"

GraffitiObject::GraffitiObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	m_GraffitiComponent = AddComponent<GraffitiComponent>();
}

void GraffitiObject::Render(std::vector<RenderInfo>& renderInfo)
{
	auto it = m_Components.find(SpriteRenderer::StaticTypeName);

	if (it != m_Components.end())
	{
		SpriteRenderer* sprite = dynamic_cast<SpriteRenderer*>(it->second.get());
		if (sprite)
		{
			RenderInfo info;
			info.bitmap = sprite->GetTexture();
			info.worldMatrix = m_Transform->GetWorldMatrix();
			info.pivot = sprite->GetPivot();
			// Opacity 적용
			info.opacity = sprite->GetOpacity();
			// UI가 아닌 일반 오브젝트 위치로 설정
			info.anchor = Anchor{ {0.0f, 0.0f}, {0.0f, 0.0f} }; // (0,0)-(0,0) 고정값
			info.anchoredPosition = m_Transform->GetPosition();
			info.sizeDelta = { 0, 0 };
			info.parentSize = { 0, 0 };
			if (m_GraffitiComponent->GetIsClicked())
			{
				info.draw = true;
			}
			else
			{
				info.draw = false;
			}

			renderInfo.push_back(info);
		}
	}
}
