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
	m_Anim->Play("droneidle");
	std::wstring key = m_Anim->GetClip()->GetTextureKey();
	std::wstring path = L"../Resource/Obstacle/" + key + L".png";
	m_Sprite->SetTexture(m_AssetManager->LoadTexture(key, path));
	m_Sprite->SetPivotPreset(SpritePivotPreset::BottomCenter, m_Sprite->GetTexture()->GetSize());
	m_Sprite->SetPath("../Resource/Obstacle/Hometown_Drone_IDLE_Ani.json");
	m_Sprite->SetTextureKey("Hometown_Drone_IDLE_Ani");
}