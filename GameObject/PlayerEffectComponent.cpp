#include "PlayerEffectComponent.h"
#include "TransformComponent.h"
#include "AnimationComponent.h"
#include "GameObject.h"
#include "SoundManager.h"

PlayerEffectComponent::~PlayerEffectComponent()
{
	GetEventDispatcher().RemoveListener(EventType::OnPlayerCollisonOccur, this);
}

void PlayerEffectComponent::Start(SoundManager* soundmanager)
{
	m_TransformComponent = m_Owner->GetComponent<TransformComponent>();
	m_AnimationComponent = m_Owner->GetComponent<AnimationComponent>();
	GetEventDispatcher().AddListener(EventType::OnPlayerCollisonOccur, this);

	m_SoundManager = soundmanager;
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
			m_SoundManager->SFX_Shot(L"run_item_pickup_hp");
		}
	}
}

void PlayerEffectComponent::Serialize(nlohmann::json& j) const
{
}

void PlayerEffectComponent::Deserialize(const nlohmann::json& j)
{
}
