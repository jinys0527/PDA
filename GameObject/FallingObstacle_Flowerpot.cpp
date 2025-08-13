#include "FallingObstacle_Flowerpot.h"
#include "AssetManager.h"

void FallingObstacle_Flowerpot::Start(AssetManager* assetManager)
{
	SetAssetManager(assetManager);
	auto& idleClips = m_AssetManager->LoadAnimation(L"Flowerpot_Idle_Ani", "../Resource/Obstacle/Flowerpot_Idle_Ani.json");

	for (const auto& [clipName, clip] : idleClips)
	{
		m_Anim->AddClip(clipName, &clip);
	}

	auto& dropClips = m_AssetManager->LoadAnimation(L"Flowerpot_Drop_Ani", "../Resource/Obstacle/Flowerpot_Drop_Ani.json");
	for (const auto& [clipName, clip] : dropClips)
	{
		m_Anim->AddClip(clipName, &clip);
	}

	auto& breakClips = m_AssetManager->LoadAnimation(L"Flowerpot_Break_Ani", "../Resource/Obstacle/Flowerpot_Break_Ani.json");
	for (const auto& [clipName, clip] : breakClips)
	{
		m_Anim->AddClip(clipName, &clip);
	}

	
	m_Sprite->SetTexture(m_AssetManager->LoadTexture(L"Flowerpot", "../Resource/Obstacle/Flowerpot.png"));
	m_Sprite->SetPivotPreset(SpritePivotPreset::BottomCenter, m_Sprite->GetTexture()->GetSize());
	m_Sprite->SetPath("../Resource/Obstacle/Flowerpot.png");
	m_Sprite->SetTextureKey("Flowerpot");
	m_Anim->Play("flowerpotidle");
}