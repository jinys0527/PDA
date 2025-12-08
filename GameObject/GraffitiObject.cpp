#include "GraffitiObject.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include "AssetManager.h"

GraffitiObject::GraffitiObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	m_GraffitiComponent = AddComponent<GraffitiComponent>();
	m_Sprite = AddComponent<SpriteRenderer>();

	srand((unsigned int)time(NULL));

	m_RandTexture = rand()%5;

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
				if (!m_GraffitiComponent->GetIsFirst()) 
				{
					info.draw = true;
				}
				else
				{
					auto iter = m_GraffitiTextures.begin();
					std::advance(iter, m_RandTexture);

					m_Sprite->SetTexture(iter->Get());
					//info.bitmap = 
				}

				info.bitmap = sprite->GetTexture();
				info.layer = m_Transform->GetZOrder();
				info.worldMatrix = m_Transform->GetWorldMatrix();
				info.pivot = sprite->GetPivot();
				// Opacity 적용
				info.opacity = sprite->GetOpacity();
				// UI가 아닌 일반 오브젝트 위치로 설정

				renderInfo.push_back(info);
			}
		}
	}
}

void GraffitiObject::SetGravittis(AssetManager* assetManager, int chapter)
{
	m_GraffitiTextures.clear();
	m_GraffitiTextures.resize(5);
	if (chapter == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			std::wstring key = L"pda_shutter" + std::to_wstring(i + 1);
			std::wstring path = L"../Resource/Background/Chapter1/" + key + L".png";
			m_GraffitiTextures[i] = assetManager->LoadTexture(key, path);
		}
	}
	else if(chapter == 2)
	{
		for (int i = 0; i < 5; i++)
		{
			std::wstring key = L"statue" + std::to_wstring(i + 1);
			std::wstring path = L"../Resource/Background/Chapter2/" + key + L".png";
			m_GraffitiTextures[i] = assetManager->LoadTexture(key, path);
		}
	}
	else if (chapter == 3 || chapter == 4)
	{
		for (int i = 0; i < 5; i++)
		{
			std::wstring key = L"Snipe";
			std::wstring path = L"../Resource/Character/Boss/" + key + L".png";
			m_GraffitiTextures[i] = assetManager->LoadTexture(key, path);
		}
	}
}

void GraffitiObject::Start(AssetManager* assetManager, int chapter)
{
	if (chapter == 1)
	{
		m_Sprite->SetTexture(assetManager->LoadTexture(L"pda_Shutter_graffiti", "../Resource/Background/Chapter1/pda_Shutter_graffiti.png"));
		m_Sprite->SetPivotPreset(SpritePivotPreset::BottomCenter, m_Sprite->GetTexture()->GetSize());
		m_Sprite->SetTextureKey("pda_Shutter_graffiti");
		m_Sprite->SetPath("../Resource/Background/Chapter1/pda_Shutter_graffiti.png");
	}
	else if (chapter == 2)
	{
		m_Sprite->SetTexture(assetManager->LoadTexture(L"statue_Grafity", "../Resource/Background/Chapter2/statue_Grafity.png"));
		m_Sprite->SetPivotPreset(SpritePivotPreset::BottomCenter, m_Sprite->GetTexture()->GetSize());
		m_Sprite->SetTextureKey("statue_Grafity");
		m_Sprite->SetPath("../Resource/Background/Chapter2/statue_Grafity.png");
	}
}
