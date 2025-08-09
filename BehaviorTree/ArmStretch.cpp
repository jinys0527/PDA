#include "ArmStretch.h"
#include "BlackBoard.h"
#include "AnimationComponent.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"

NodeState ArmStretch::Tick(BlackBoard& bb, float deltaTime)
{
#pragma region Initialize
	if (!m_Initialized)
    {
        m_Telegraphs = bb.GetValue<std::vector<std::shared_ptr<Telegraph>>>("BossTelegraph").value();
        m_Anims = bb.GetValue<std::vector<std::shared_ptr<GameObject>>>("BossAnims").value();
        m_MoveDuration = m_Anims[0]->GetComponent<AnimationComponent>()->GetTotalDuration("attack");

        m_AttackRange = bb.GetValue<std::vector<int>>(m_Name).value();

        for (int idx : m_AttackRange)
        {
            if (m_minIndex > idx)
            {
                m_minIndex = idx;
            }
            if (m_maxIndex < idx)
            {
                m_maxIndex = idx;
            }
        }
        m_MoveStartPos = m_Telegraphs[m_minIndex]->GetInitPos();
        m_MoveTargetPos = m_Telegraphs[m_maxIndex]->GetInitPos();

        m_Initialized = true;

    }
#pragma endregion

    if (!m_HasStarted)
    {
        StartWarning(bb);
        m_HasStarted = true;
    }

    m_ElapsedTime += deltaTime;

    // 애니메이션 비활성화 타이머 (이게 먼저 와야 Success 전에 실행됨)
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

    // 이동은 공격 시작 여부와 무관하게 매 프레임 처리
    if (m_IsMoving)
    {
        m_MoveTimer += deltaTime;
        float t = m_MoveTimer / m_MoveDuration;
        if (t > 1.0f) t = 1.0f;

        auto trans = m_Telegraphs[m_minIndex]->GetComponent<TransformComponent>();
        Math::Vector2F currPos;
        currPos.x = m_MoveStartPos.x + (m_MoveTargetPos.x - m_MoveStartPos.x) * t;
        currPos.y = m_MoveStartPos.y + (m_MoveTargetPos.y - m_MoveStartPos.y) * t;

        trans->SetPosition(currPos);

        if (t >= 1.0f)
        {
            m_IsMoving = false; // 이동 완료
            m_Telegraphs[m_minIndex]->SetColliderActive(false);
        }
    }

    return NodeState::Running;

}

void ArmStretch::StartWarning(BlackBoard& bb)
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

void ArmStretch::EndWarning(BlackBoard& bb)
{
    std::cout << m_Name << " 공격" << std::endl;

    for (int idx : m_AttackRange)
    {
        auto& telegraph = m_Telegraphs[idx];
        if (telegraph)
        {
            telegraph->SetInactive();
            //telegraph->SetColliderActive();
        }
    }

    m_Telegraphs[m_minIndex]->SetColliderActive(true);

    m_IsMoving = true;


    // 애니메이션 재생
    m_Anims[0]->GetComponent<TransformComponent>()->SetPosition(m_MoveStartPos);
    auto anim = m_Anims[0]->GetComponent<AnimationComponent>();
    anim->SetIsActive(true);
    anim->Play();
    auto sprite = m_Anims[0]->GetComponent<SpriteRenderer>();
    sprite->SetIsActive(1);
    sprite->SetOpacity(1);

    m_AnimPlaying = true;
    m_AnimTimer = 0.0f;

}

void ArmStretch::Reset()
{
    __super::Reset();
    m_MoveTimer = 0.0f;

    m_Telegraphs[m_minIndex]->GetComponent<TransformComponent>()->SetPosition(m_MoveStartPos);

}
