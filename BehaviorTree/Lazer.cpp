#include "Lazer.h"
#include "BlackBoard.h"
#include "AnimationComponent.h"
#include "SpriteRenderer.h"

NodeState Lazer::Tick(BlackBoard& bb, float deltaTime)
{
#pragma region Initialize
    if (!m_Initialized)
    {
        m_Telegraphs = bb.GetValue<std::vector<std::shared_ptr<Telegraph>>>("BossTelegraph").value();
        m_Anims = bb.GetValue<std::vector<std::shared_ptr<GameObject>>>("BossAnims").value();

        m_AttackRange = bb.GetValue<std::vector<int>>(m_Name).value();
        m_minIndex = m_AttackRange.front();
        m_maxIndex = m_AttackRange.back();

        m_StartTelIndex = (m_minIndex + m_maxIndex) / 2;

        m_Initialized = true;
    }

#pragma endregion

    if (!m_HasStarted)
    {
        bb.GetSoundManager().SFX_Shot(L"boss_laser_charge");
        bb.GetSoundManager().SFX_Shot(L"boss_warning_beep");

        StartWarning(bb);
        m_HasStarted = true;
    }

    m_ElapsedTime += deltaTime;

    if (m_IsActivating)
    {
        // 첫 프레임: 중앙 활성화
        if (m_ActivateStep == 0)
        {
            m_Telegraphs[m_StartTelIndex]->SetColliderActive(true);
            m_Telegraphs[m_StartTelIndex]->SetActive();

            m_PrevLeft = m_StartTelIndex;
            m_PrevRight = m_StartTelIndex;
            m_ActivateStep = 1;
        }

        // 다음 프레임들: 좌우 확장
        m_ActivateTimer += deltaTime;
        if (m_ActivateTimer >= 0.3f)
        {
            int curLeft = m_StartTelIndex - m_ActivateStep;
            int curRight = m_StartTelIndex + m_ActivateStep;

            if (curLeft >= m_minIndex)
            {
                m_Telegraphs[curLeft]->SetColliderActive(true);
                m_Telegraphs[curLeft]->SetActive();
                //m_Telegraphs[curLeft]->SetActiveAnimation();
            }
            if (curRight <= m_maxIndex)
            {
                m_Telegraphs[curRight]->SetColliderActive(true);
                m_Telegraphs[curRight]->SetActive();
                //m_Telegraphs[curRight]->SetActiveAnimation();

            }

            // 이전 거 끄기
            if (m_PrevLeft >= 0) 
            {
                m_Telegraphs[m_PrevLeft]->SetColliderActive(false);
                m_Telegraphs[m_PrevLeft]->SetInactive();
            }
            if (m_PrevRight >= 0) 
            {
                m_Telegraphs[m_PrevRight]->SetColliderActive(false);
                m_Telegraphs[m_PrevRight]->SetInactive();
            }

            m_PrevLeft = curLeft;
            m_PrevRight = curRight;

            m_ActivateStep++;
            m_ActivateTimer = 0.0f;

            // 다 했으면 종료
            // 하드코딩임 고쳐야 함
            if (curLeft < m_minIndex && curRight > m_maxIndex)
            {
                m_IsActivating = false;
            }
        }
    }



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
            bb.GetSoundManager().SFX_Shot(L"boss_laser_fire");

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

void Lazer::StartWarning(BlackBoard& bb)
{
    std::cout << m_Name << " 경고" << std::endl;

    for (int idx : m_AttackRange)
    {
        auto& telegraph = m_Telegraphs[idx];

        if (telegraph)
        {
            //telegraph->SetActive();
        }
    }

}

void Lazer::EndWarning(BlackBoard& bb)
{
    std::cout << m_Name << " 공격" << std::endl;

    for (int idx : m_AttackRange)
    {
        auto& telegraph = m_Telegraphs[idx];
        if (telegraph)
        {
            telegraph->SetInactive();
        }
    }

    m_ActivateStep = 0;
    m_ActivateTimer = 0.0f;
    m_IsActivating = true;

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

void Lazer::Reset()
{
    __super::Reset();
    m_ActivateStep = 0;
    m_ActivateTimer = 0.0f;
}
