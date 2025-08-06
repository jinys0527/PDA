#include "AnimationComponent.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "AssetManager.h"

void AnimationComponent::Play(const std::string& name, bool loop /*= true*/)
{
	if (m_CurrentClipName == name) return;

	m_AnimationController.SetClip(m_Clips[name]);
	m_AnimationController.SetLooping(loop);
	m_AnimationController.SetElapsed(0.f);
	m_CurrentClipName = name;
}

void AnimationComponent::Update(float deltaTime)
{
	m_AnimationController.Update(deltaTime);
	const Frame& frame = m_AnimationController.GetCurrentFrame();
	
	const AnimationClip* currentClip = m_Clips[m_CurrentClipName];
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> texture = m_AssetManager->GetTexture(currentClip->GetTextureKey());
	if (!texture)
		return;

	auto sr = m_Owner->GetComponent<SpriteRenderer>();
	sr->SetTexture(texture, frame.ToRectF());
}

void AnimationComponent::OnEvent(EventType type, const void* data)
{

}

void AnimationComponent::Serialize(nlohmann::json& j) const
{
}

void AnimationComponent::Deserialize(const nlohmann::json& j)
{
}
