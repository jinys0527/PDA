#include "SkillNode.h"
#include "BlackBoard.h"

NodeState SkillNode::Tick(BlackBoard& bb, float deltaTime)
{
    if (!m_Initialized)
    {
        m_Telegraphs = bb.GetValue<std::vector<std::shared_ptr<Telegraph>>>("BossTelegraph").value();

        if (m_Name == "Skill_1_Warning")
        {
            m_AttackRange = bb.GetValue<std::vector<int>>("Skill_1").value();
        }
        else if (m_Name == "Skill_2_Warning")
        {
            m_AttackRange = bb.GetValue<std::vector<int>>("Skill_2").value();
        }
        else if (m_Name == "Skill_3_Warning")
        {
            m_AttackRange = bb.GetValue<std::vector<int>>("Skill_3").value();
        }

        m_Initialized = true;
    }

    if (!m_HasStarted)
    {
        // 경고 이펙트 시작
        StartWarning(bb);
        m_HasStarted = true;
    }

    m_ElapsedTime += deltaTime;

    if (m_ElapsedTime >= m_WarningTime)
    {
        // 경고 시간 끝 → 데미지 등 실행
        EndWarning(bb);
        Reset(); // 다음 Tick을 위해 초기화
        return NodeState::Success;
    }

    return NodeState::Running;
}

void SkillNode::StartWarning(BlackBoard& bb)
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

void SkillNode::EndWarning(BlackBoard& bb)
{
    std::cout << m_Name << " 공격" << std::endl;
    for (int idx : m_AttackRange)
    {
        auto& telegraph = m_Telegraphs[idx];

        if (telegraph)
        {
            telegraph->SetInactive();
            telegraph->SetColliderActive();
        }
    }

}

void SkillNode::Reset()
{
    m_ElapsedTime = 0.0f;
    m_HasStarted = false;
}
