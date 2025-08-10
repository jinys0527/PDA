#include "PlayerEffectComponent.h"
#include "TransformComponent.h"
#include "AnimationComponent.h"
#include "GameObject.h"

PlayerEffectComponent::~PlayerEffectComponent()
{
	GetEventDispatcher().RemoveListener(EventType::OnPlayerCollisonOccur, this);
}

void PlayerEffectComponent::Start()
{
	m_TransformComponent = m_Owner->GetComponent<TransformComponent>();
	m_AnimationComponent = m_Owner->GetComponent<AnimationComponent>();
	GetEventDispatcher().AddListener(EventType::OnPlayerCollisonOccur, this);
}

void PlayerEffectComponent::Update(float deltaTime)
{
	Math::Vector2F pos = { 0, 0 };

	if (m_AnimationComponent->IsAnimationFinished())
		pos.y = 5000;
	m_TransformComponent->SetPosition(pos);
}

void PlayerEffectComponent::OnEvent(EventType type, const void* data)
{
	if (EventType::OnPlayerCollisonOccur == type)
	{
		if ((int)data < 0)
		{
			m_AnimationComponent->Finish();
			m_AnimationComponent->Play("heal", false);
		}
	}
}

void PlayerEffectComponent::Serialize(nlohmann::json& j) const
{
}

void PlayerEffectComponent::Deserialize(const nlohmann::json& j)
{
}
