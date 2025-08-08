#include "Telegraph.h"
#include "BoxColliderComponent.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"

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
    }

    if (!m_IsWaving) return;

    m_Time += deltaTime;

    float opacity = 0.5f + 0.5f * sinf(m_Time * m_FadeSpeed);  // 0 ~ 1로 부드럽게 왔다갔다

    auto sr = GetComponent<SpriteRenderer>();
    if (sr)
        sr->SetOpacity(opacity);
}

void Telegraph::SetActive()
{
    m_IsWaving = true;
    m_Opacity = 0.f;

    auto sr = GetComponent<SpriteRenderer>();
    if (sr)
        sr->SetOpacity(m_Opacity);
}

void Telegraph::SetInactive()
{
    m_IsWaving = false;
    m_Time = 0.0f;

    auto sr = GetComponent<SpriteRenderer>();
    if (sr)
        sr->SetOpacity(0.0f);
}

void Telegraph::SetColliderActive()
{
	auto box = GetComponent<BoxColliderComponent>();
	box->SetIsActive(true);
}
