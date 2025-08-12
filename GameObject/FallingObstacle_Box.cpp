#include "FallingObstacle_Box.h"
#include "AssetManager.h"

void FallingObstacle_Box::Start(AssetManager* assetManager)
{
	SetAssetManager(assetManager);
	m_Sprite->SetTexture(m_AssetManager->LoadTexture(L"box", "../Resource/Obstacle/box.png"));
	m_Sprite->SetPivotPreset(SpritePivotPreset::BottomCenter, m_Sprite->GetTexture()->GetSize());
	m_Sprite->SetTextureKey("box");
	m_Sprite->SetPath("../Resource/Obstacle/box.png");
}