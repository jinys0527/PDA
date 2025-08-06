#include "SkillNode.h"

NodeState SkillNode::Tick(BlackBoard& bb, float deltaTime)
{
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
}

void SkillNode::EndWarning(BlackBoard& bb)
{
    std::cout << m_Name << " 공격" << std::endl;
}

void SkillNode::Reset()
{
    m_ElapsedTime = 0.0f;
    m_HasStarted = false;
}
