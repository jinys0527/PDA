#include "Pick.h"
#include "BlackBoard.h"
#include "AnimationComponent.h"
#include "SpriteRenderer.h"

NodeState Pick::Tick(BlackBoard& bb, float deltaTime)
{
#pragma region Initialize
    if (!m_Initialized)
    {
        m_Telegraphs = bb.GetValue<std::vector<std::shared_ptr<Telegraph>>>("BossTelegraph").value();
        m_Anims = bb.GetValue<std::vector<std::shared_ptr<GameObject>>>("BossAnims").value();

        //임시
        m_AttackRange = bb.GetValue<std::vector<int>>(m_Name).value();

        m_Initialized = true;
    }
#pragma endregion

    if (!m_HasStarted)
    {
        StartWarning(bb);
        m_HasStarted = true;
    }

    m_ElapsedTime += deltaTime;


    if (m_AnimPlaying)
    {
        if (m_Anims[0]->GetComponent<AnimationComponent>()->IsAnimationFinished())
        {
            m_Anims[0]->GetComponent<AnimationComponent>()->SetIsActive(false);
            auto sprite = m_Anims[0]->GetComponent<SpriteRenderer>();
            sprite->SetIsActive(0);
            sprite->SetOpacity(0);
            m_AnimPlaying = false;
        }
    }

    if (m_ElapsedTime >= m_WarningTime)
    {
        if (!m_AttackStarted)
        {
            EndWarning(bb);
            m_AttackStarted = true;
        }

        // 애니메이션 끝났는지 체크
        if (!m_AnimPlaying)
        {
            Reset();
            return NodeState::Success;
        }
    }


    return NodeState::Running;
}

void Pick::StartWarning(BlackBoard& bb)
{
    std::cout << m_Name << " 경고" << std::endl;

    for (int idx : m_AttackRange)
    {
        auto& telegraph = m_Telegraphs[idx];

        if (telegraph)
        {
            telegraph->SetActive();
        }
    }
}

void Pick::EndWarning(BlackBoard& bb)
{
    std::cout << m_Name << " 공격" << std::endl;

    for (int idx : m_AttackRange)
    {
        auto& telegraph = m_Telegraphs[idx];
        if (telegraph)
        {
            telegraph->SetInactive();
            telegraph->SetColliderActive(true);
        }
    }

    // 애니메이션 재생
    auto anim = m_Anims[0]->GetComponent<AnimationComponent>();
    anim->SetIsActive(true);
    anim->Play();
    auto sprite = m_Anims[0]->GetComponent<SpriteRenderer>();
    sprite->SetIsActive(1);
    sprite->SetOpacity(1);

    m_AnimPlaying = true;
    m_AnimTimer = 0.0f;

}

void Pick::Reset()
{
	__super::Reset();

    for (int idx : m_AttackRange)
    {
        auto& telegraph = m_Telegraphs[idx];
        if (telegraph)
        {
            telegraph->SetColliderActive(false);
        }
    }

}
