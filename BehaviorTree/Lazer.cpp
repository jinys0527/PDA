#include "Lazer.h"
#include "BlackBoard.h"
#include "AnimationComponent.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"

NodeState Lazer::Tick(BlackBoard& bb, float deltaTime)
{
#pragma region Initialize
    if (!m_Initialized)
    {
        m_Telegraphs = bb.GetValue<std::vector<std::shared_ptr<Telegraph>>>("BossTelegraph").value();
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
        // ù ������: �߾� Ȱ��ȭ
        if (m_ActivateStep == 0)
        {
            m_Telegraphs[m_StartTelIndex]->SetColliderActive(true);

            m_PrevLeft = m_StartTelIndex;
            m_PrevRight = m_StartTelIndex;
            m_ActivateStep = 1;
        }

        // ���� �����ӵ�: �¿� Ȯ��
        m_ActivateTimer += deltaTime;
        if (m_ActivateTimer >= 0.3f)
        {
            int curLeft = m_StartTelIndex - m_ActivateStep;
            int curRight = m_StartTelIndex + m_ActivateStep;

            if (curLeft >= m_minIndex)
            {
                m_Telegraphs[curLeft]->SetColliderActive(true);
                //m_Telegraphs[curLeft]->SetActiveAnimation();
            }
            if (curRight <= m_maxIndex)
            {
                m_Telegraphs[curRight]->SetColliderActive(true);
                //m_Telegraphs[curRight]->SetActiveAnimation();

            }

            // ���� �� ����
            if (m_PrevLeft >= 0) 
            {
                m_Telegraphs[m_PrevLeft]->SetColliderActive(false);
            }
            if (m_PrevRight >= 0) 
            {
                m_Telegraphs[m_PrevRight]->SetColliderActive(false);
            }

            m_PrevLeft = curLeft;
            m_PrevRight = curRight;

            m_ActivateStep++;
            m_ActivateTimer = 0.0f;

            // �� ������ ����
            // �ϵ��ڵ��� ���ľ� ��
            if (curLeft < m_minIndex && curRight > m_maxIndex)
            {
                m_IsActivating = false;
            }
        }
    }



    if (m_AnimPlaying && m_CurrentAnimObj)
    {
        auto animComp = m_CurrentAnimObj->GetComponent<AnimationComponent>();
        if (animComp->IsAnimationFinished())
        {
            animComp->SetIsActive(false);
            auto sprite = m_CurrentAnimObj->GetComponent<SpriteRenderer>();
            sprite->SetIsActive(false);
            sprite->SetOpacity(0);

            m_AnimPlaying = false;

            // ���� ������ �ִϸ��̼� �̸� �����忡�� ����
            auto runningAnimsOpt = bb.GetValue<std::vector<std::string>>("RunningAnims");
            if (runningAnimsOpt.has_value())
            {
                auto runningAnims = runningAnimsOpt.value();
                auto it = std::find(runningAnims.begin(), runningAnims.end(), m_Name);
                if (it != runningAnims.end())
                {
                    runningAnims.erase(it);
                    bb.SetValue("RunningAnims", runningAnims);
                }
            }

            m_CurrentAnimObj = nullptr;
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

        // ���� ���� �ִϸ��̼��� �ϳ��� ���� ������ ��� Running
        auto runningAnimsOpt = bb.GetValue<std::vector<std::string>>("RunningAnims");
        if (runningAnimsOpt.has_value() && !runningAnimsOpt.value().empty())
        {
            return NodeState::Running;
        }


        Reset();
        return NodeState::Success;
    }
    return NodeState::Running;


}

void Lazer::StartWarning(BlackBoard& bb)
{
    std::cout << m_Name << " ���" << std::endl;

    for (int idx : m_AttackRange)
    {
        auto& telegraph = m_Telegraphs[idx];

        if (telegraph)
        {
            telegraph->SetActive();
        }
    }
    // ��� �ִϸ��̼� ����
    auto animObj = GetAvailableAnim(bb, "Boss_Lazer");  // ���� �ִϸ��̼� Ű����
    if (animObj)
    {
        m_CurrentAnimObj = animObj;

        if (!m_AttackRange.empty())
        {
            // ��ġ ���� (���ϴ� ��ġ�� ���� ����)
            float posX = m_Telegraphs[m_StartTelIndex]->GetComponent<TransformComponent>()->GetPosition().x + 750.f;
            float posY = m_Telegraphs[m_StartTelIndex]->GetComponent<TransformComponent>()->GetPosition().y - 150.f;

            animObj->GetComponent<TransformComponent>()->SetPosition({ posX, posY });
        }

        auto animComp = m_CurrentAnimObj->GetComponent<AnimationComponent>();
        animComp->SetIsActive(true);
        animComp->Play("charge");  // �ִϸ��̼� Ŭ�� �̸�(����)
        animComp->SetLoop(true);    // ���ϱ� ���� ���� ����

        auto sprite = m_CurrentAnimObj->GetComponent<SpriteRenderer>();
        sprite->SetIsActive(true);
        sprite->SetOpacity(1);

        m_AnimPlaying = true;
    }
}

void Lazer::EndWarning(BlackBoard& bb)
{
    std::cout << m_Name << " ����" << std::endl;

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

    if (!m_AttackRange.empty())
    {
        float posX = m_Telegraphs[m_StartTelIndex]->GetComponent<TransformComponent>()->GetPosition().x + 750.f;
        float posY = m_Telegraphs[m_StartTelIndex]->GetComponent<TransformComponent>()->GetPosition().x - 1300.f;

        m_CurrentAnimObj->GetComponent<TransformComponent>()->SetPosition({ posX, posY });
    }

    auto animComp = m_CurrentAnimObj->GetComponent<AnimationComponent>();

    animComp->Play("fire");
    animComp->SetLoop(false);

    animComp->SetIsActive(true);

    auto sprite = m_CurrentAnimObj->GetComponent<SpriteRenderer>();
    sprite->SetIsActive(true);
    sprite->SetOpacity(1);

    // ���� ���� �� �����忡 �ִϸ��̼� �̸� �߰�
    auto runningAnimsOpt = bb.GetValue<std::vector<std::string>>("RunningAnims");
    if (!runningAnimsOpt.has_value())
    {
        bb.SetValue("RunningAnims", std::vector<std::string>{ m_Name });
    }
    else
    {
        auto runningAnims = runningAnimsOpt.value();
        runningAnims.push_back(m_Name);
        bb.SetValue("RunningAnims", runningAnims);
    }

    m_AnimPlaying = true;
    
}

void Lazer::Reset()
{
    __super::Reset();
    m_ActivateStep = 0;
    m_ActivateTimer = 0.0f;
}
