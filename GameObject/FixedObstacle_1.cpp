#include "FixedObstacle_1.h"
#include "AssetManager.h"

void FixedObstacle_1::Start(AssetManager* assetManager)
{
	SetAssetManager(assetManager);
	m_Sprite->SetTexture(m_AssetManager->LoadTexture(L"Garbage_bag", "../Resource/Obstacle/Garbage_bag.png"));
	m_Sprite->SetPivotPreset(SpritePivotPreset::BottomCenter, m_Sprite->GetTexture()->GetSize());
	m_Sprite->SetTextureKey("Garbage_bag");
	m_Sprite->SetPath("../Resource/Obstacle/Garbage_bag.png");
}