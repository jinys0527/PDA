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
		for (auto& comp : it->second)
		{
			SpriteRenderer* sprite = dynamic_cast<SpriteRenderer*>(comp.get());
			if (sprite)
			{
				RenderInfo info;
				info.bitmap = sprite->GetTexture();
				info.worldMatrix = m_Transform->GetWorldMatrix();
				info.pivot = sprite->GetPivot();
				// Opacity ����
				info.opacity = sprite->GetOpacity();
				// UI�� �ƴ� �Ϲ� ������Ʈ ��ġ�� ����

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
}
