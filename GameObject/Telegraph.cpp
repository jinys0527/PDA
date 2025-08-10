#include "Telegraph.h"
#include "BoxColliderComponent.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include "AnimationComponent.h"

#include <cmath>

Telegraph::Telegraph(EventDispatcher& eventDispatcher) : Obstacle(eventDispatcher)
{
	auto box = GetComponent<BoxColliderComponent>();
    box->SetIsActive(false);
    
}

void Telegraph::Update(float deltaTime)
{
    if (!m_IsInitialized)
    {
        auto trans = GetComponent<TransformComponent>();
        m_InitPos = trans->GetPosition();

        m_WarningTexture = GetComponent<SpriteRenderer>()->GetTexture();
        m_IsInitialized = true;
    }

    if (m_IsWaving)
    {
        m_Time += deltaTime;

        float opacity = 0.5f + 0.5f * sinf(m_Time * m_FadeSpeed);  // 0 ~ 1로 부드럽게 왔다갔다

        auto sr = GetComponent<SpriteRenderer>();
        if (sr)
            sr->SetOpacity(opacity);
    }

    if (m_IsAnimationPlaying)
    {
        if (auto anim = GetComponent<AnimationComponent>()->IsAnimationFinished())
        {
            SetInactive();
        }
    }
}

void Telegraph::SetActive()
{
    m_IsWaving = true;
    m_Opacity = 0.f;

    auto sr = GetComponent<SpriteRenderer>();
    if (sr)
    {
        sr->SetOpacity(m_Opacity);
        sr->SetTexture(m_WarningTexture);
    }
}

void Telegraph::SetInactive()
{
    m_IsWaving = false;
    m_Time = 0.0f;

    auto sr = GetComponent<SpriteRenderer>();
    if (sr)
        sr->SetOpacity(0.0f);
}

void Telegraph::SetColliderActive(bool active)
{
	auto box = GetComponent<BoxColliderComponent>();
	box->SetIsActive(active);
}

void Telegraph::SetActiveAnimation()
{
    auto anim = GetComponent<AnimationComponent>();
    anim->SetIsActive(true);
    anim->Play();
    auto sprite = GetComponent<SpriteRenderer>();
    sprite->SetOpacity(1);
    m_IsAnimationPlaying = true;
}

void Telegraph::SetInactiveAnimation()
{
    auto anim = GetComponent<AnimationComponent>();
    anim->SetIsActive(false);
    auto sprite = GetComponent<SpriteRenderer>();
    sprite->SetOpacity(0);

    m_IsAnimationPlaying = false;

}