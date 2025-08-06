#include "SkillNode.h"

NodeState SkillNode::Tick(BlackBoard& bb, float deltaTime)
{
    if (!m_HasStarted)
    {
        // ��� ����Ʈ ����
        StartWarning(bb);
        m_HasStarted = true;
    }

    m_ElapsedTime += deltaTime;

    if (m_ElapsedTime >= m_WarningTime)
    {
        // ��� �ð� �� �� ������ �� ����
        EndWarning(bb);
        Reset(); // ���� Tick�� ���� �ʱ�ȭ
        return NodeState::Success;
    }

    return NodeState::Running;
}

void SkillNode::StartWarning(BlackBoard& bb)
{
    std::cout << m_Name << " ���" << std::endl;
}

void SkillNode::EndWarning(BlackBoard& bb)
{
    std::cout << m_Name << " ����" << std::endl;
}

void SkillNode::Reset()
{
    m_ElapsedTime = 0.0f;
    m_HasStarted = false;
}
