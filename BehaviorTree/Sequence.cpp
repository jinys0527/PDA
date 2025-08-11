#include "Sequence.h"

NodeState Sequence::Tick(BlackBoard& bb, float deltaTime)
{
    // m_CurrentIndex���� �ڽ� ����
    while (m_CurrIndex < m_Children.size()) {
        NodeState result = m_Children[m_CurrIndex]->Tick(bb, deltaTime);

        //if (m_Name == "P1_Skill_1" || m_Name == "P1_Skill_2" || m_Name == "P1_Skill_3" || m_Name == "P1_Skill_4" || m_Name == "P1_Skill_5")
        //{
        //    std::cout << "Sequence Tick - m_Name: " << m_Name
        //        << ", ���� �ε���: " << m_CurrIndex
        //        << ", ���: " << static_cast<int>(result) << std::endl;
        //}
        
        if (result == NodeState::Running) 
        {
            return NodeState::Running;
        }
        else if (result == NodeState::Failure) 
        {
            m_CurrIndex = 0;
            return NodeState::Failure;
        }

        ++m_CurrIndex;
    }

    m_CurrIndex = 0;

    return NodeState::Success;
}