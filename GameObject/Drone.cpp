#include "Drone.h"
#include "SpriteRenderer.h"
#include "AnimationComponent.h"
#include "AssetManager.h"

void Drone::Start(AssetManager* assetManager)
{
	SetAssetManager(assetManager);
	auto& idleClips = m_AssetManager->LoadAnimation(L"Hometown_Drone_IDLE_Ani", "../Resource/Obstacle/Hometown_Drone_IDLE_Ani.json");

	for (const auto& [clipName, clip] : idleClips)
	{
		m_Anim->AddClip(clipName, &clip);
	}

	auto& dropClips = m_AssetManager->LoadAnimation(L"Hometown_Drone_Drop_Ani", "../Resource/Obstacle/Hometown_Drone_Drop_Ani.json");
	for (const auto& [clipName, clip] : dropClips)
	{
		m_Anim->AddClip(clipName, &clip);
	}

	m_Sprite->SetTexture(m_AssetManager->LoadTexture(L"Hometown_Drone_IDLE", "../Resource/Obstacle/Hometown_Drone_IDLE.png"));
	m_Sprite->SetPivotPreset(SpritePivotPreset::BottomCenter, m_Sprite->GetTexture()->GetSize());
	m_Sprite->SetPath("../Resource/Obstacle/Hometown_Drone_IDLE.png");
	m_Sprite->SetTextureKey("Hometown_Drone_IDLE");
	m_Anim->Play("droneidle");
}