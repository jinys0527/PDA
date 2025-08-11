#include "Sequence.h"

NodeState Sequence::Tick(BlackBoard& bb, float deltaTime)
{
    // m_CurrentIndex부터 자식 실행
    while (m_CurrIndex < m_Children.size()) {
        NodeState result = m_Children[m_CurrIndex]->Tick(bb, deltaTime);

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