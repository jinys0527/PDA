#include "SlidingObstacle.h"
#include "AssetManager.h"

void SlidingObstacle::Start(AssetManager* assetManager)
{
	SetAssetManager(assetManager);
	m_Sprite->SetTexture(m_AssetManager->LoadTexture(L"Drone", "../Resource/Obstacle/Drone.png"));
	m_Sprite->SetPivotPreset(SpritePivotPreset::BottomCenter, m_Sprite->GetTexture()->GetSize());
	m_Sprite->SetTextureKey("Drone");
	m_Sprite->SetPath("../Resource/Obstacle/Drone.png");
}