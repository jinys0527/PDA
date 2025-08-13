#include "Pick.h"
#include "BlackBoard.h"
#include "AnimationComponent.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"

NodeState Pick::Tick(BlackBoard& bb, float deltaTime)
{
    if (!m_Initialized)
    {
        m_Telegraphs = bb.GetValue<std::vector<std::shared_ptr<Telegraph>>>("BossTelegraph").value();
        m_AttackRange = bb.GetValue<std::vector<int>>(m_Name).value();

        m_Initialized = true;
    }

    if (!m_HasStarted)
    {

        bb.GetSoundManager().SFX_Shot(L"boss_warning_beep");
        StartWarning(bb);
        m_HasStarted = true;
    }

    m_ElapsedTime += deltaTime;

    if (m_AnimPlaying && m_CurrentAnimObj)
    {
        m_AttackElapsedTime += deltaTime;

        // 5������ ~ 8������ ���̿��� �ݶ��̴� �ѱ�
        if (!m_ColliderOn && m_AttackElapsedTime >= 0.5f && m_AttackElapsedTime < 0.8f)
        {
            for (int idx : m_AttackRange)
                if (m_Telegraphs[idx]) m_Telegraphs[idx]->SetColliderActive(true);
            m_ColliderOn = true;
        }

        // 8������ ���Ŀ��� �ݶ��̴� ����
        if (m_ColliderOn && m_AttackElapsedTime >= 0.8f)
        {
            for (int idx : m_AttackRange)
                if (m_Telegraphs[idx]) m_Telegraphs[idx]->SetColliderActive(false);
            m_ColliderOn = false;
        }        auto animComp = m_CurrentAnimObj->GetComponent<AnimationComponent>();

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
            bb.GetSoundManager().SFX_Shot(L"boss_arm_slam_stab");
            EndWarning(bb);
            m_AttackStarted = true;
        }

        // ���� ���� �ִϸ��̼��� �ϳ��� ���� ������ ��� Running
        auto runningAnimsOpt = bb.GetValue<std::vector<std::string>>("RunningAnims");
        if (runningAnimsOpt.has_value() && !runningAnimsOpt.value().empty())
        {
            return NodeState::Running;
        }

        // ������ ���� ��ȯ
        Reset();
        return NodeState::Success;
    }

    return NodeState::Running;
}

void Pick::StartWarning(BlackBoard& bb)
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
}

void Pick::EndWarning(BlackBoard& bb)
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

    
    std::shared_ptr<GameObject> animObj;
    if (bb.GetValue<int>("CurrPhase").value() == 1)
    {
        animObj = GetAvailableAnim(bb, "Boss_Pick");
    }
    else if (bb.GetValue<int>("CurrPhase").value() == 3)
    {
        animObj = GetAvailableAnim(bb, "Boss_Phase3_Pick");
    }

    if (animObj)
    {
        m_CurrentAnimObj = animObj;

        if (!m_AttackRange.empty())
        {
            int idx = m_AttackRange[0];
            auto pos = m_Telegraphs[idx]->GetInitPos();
            pos.y -= 20.f;  // ��ġ ����

            auto trans = m_CurrentAnimObj->GetComponent<TransformComponent>();
            trans->SetPosition(pos);
        }

        auto animComp = m_CurrentAnimObj->GetComponent<AnimationComponent>();
        animComp->SetIsActive(true);
        animComp->Play();

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
}

void Pick::Reset()
{
    __super::Reset();

    //m_ElapsedTime = 0.f;
    //m_HasStarted = false;
    //m_AttackStarted = false;

    for (int idx : m_AttackRange)
    {
        auto& telegraph = m_Telegraphs[idx];
        if (telegraph)
            telegraph->SetColliderActive(false);
    }
}