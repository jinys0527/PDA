#include "GraffitiObject.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include "AssetManager.h"

GraffitiObject::GraffitiObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	m_GraffitiComponent = AddComponent<GraffitiComponent>();

	srand((unsigned int)time(NULL));
	m_RandTexture = rand();
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
				// Opacity 적용
				info.opacity = sprite->GetOpacity();
				// UI가 아닌 일반 오브젝트 위치로 설정

				if (!m_GraffitiComponent->GetIsClicked())
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



	{
		auto iter = m_GraffitiTextures.begin();
		std::advance(iter, m_RandTexture);

			RenderInfo info;
			info.bitmap = iter->Get();
			info.worldMatrix = m_Transform->GetWorldMatrix();
			Math::Vector2F pivot = { iter->Get()->GetSize().width * 0.5f, iter->Get()->GetSize().height * 0.5f };
			info.pivot = pivot;
			// Opacity 적용
			info.opacity = 1;
			// UI가 아닌 일반 오브젝트 위치로 설정

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

void GraffitiObject::SetGravitti(AssetManager* assetManager)
{
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"brick", L"../Resource/bricks.png"));
	//m_GraffitiTextures.push_back(assetManager->LoadTexture(L"cat_texture", L"../Resource/cat_texture.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"test", L"../Resource/test.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"test1", L"../Resource/test1.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"test2", L"../Resource/test2.png"));

	m_RandTexture = m_RandTexture % m_GraffitiTextures.size();
}
