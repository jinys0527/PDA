#include "AnimationComponent.h"

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
