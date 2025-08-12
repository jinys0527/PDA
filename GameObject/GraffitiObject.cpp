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
			D2D1::Matrix3x2F worldSize = D2D1::Matrix3x2F::Identity();
			D2D1_SIZE_F bitSize = info.bitmap.Get()->GetSize();
			float ratio = 512 / bitSize.width;
			worldSize.m11 = ratio;
			worldSize.m22 = ratio;
			info.worldMatrix = worldSize * m_Transform->GetWorldMatrix();
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
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"sour", L"../Resource/Character/Sour/Graffiti/SOUR.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"01", L"../Resource/Character/Sour/Graffiti/01.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"02", L"../Resource/Character/Sour/Graffiti/02.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"03", L"../Resource/Character/Sour/Graffiti/03.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"04", L"../Resource/Character/Sour/Graffiti/04.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"pda", L"../Resource/Character/Sour/Graffiti/pda.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"IWantToGoHome", L"../Resource/Character/Sour/Graffiti/IWantToGoHome.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"Yoon", L"../Resource/Character/Sour/Graffiti/Yoon.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"Hye", L"../Resource/Character/Sour/Graffiti/Hye.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"Saze", L"../Resource/Character/Sour/Graffiti/Saze.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"Video", L"../Resource/Character/Sour/Graffiti/Video.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"ddhhssjj", L"../Resource/Character/Sour/Graffiti/ddhhssjj.png"));
	m_GraffitiTextures.push_back(assetManager->LoadTexture(L"DoTheZac", L"../Resource/Character/Sour/Graffiti/DoTheZac.png"));

	m_RandTexture = m_RandTexture % m_GraffitiTextures.size();
}