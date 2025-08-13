#include "FixedObstacle_2.h"
#include "AssetManager.h"

void FixedObstacle_2::Start(AssetManager* assetManager)
{
	SetAssetManager(assetManager);
	m_Sprite->SetTexture(m_AssetManager->LoadTexture(L"Wastebasket", "../Resource/Obstacle/Wastebasket.png"));
	m_Sprite->SetPivotPreset(SpritePivotPreset::BottomCenter, m_Sprite->GetTexture()->GetSize());
	m_Sprite->SetTextureKey("Wastebasket");
	m_Sprite->SetPath("../Resource/Obstacle/Wastebasket.png");
}