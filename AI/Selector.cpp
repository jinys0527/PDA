#include "Selector.h"

NodeState Selector::Tick(BlackBoard& bb)
{
    while (m_CurrIndex < m_Children.size())
    {
        NodeState result = m_Children[m_CurrIndex]->Tick(bb);

        if (result == NodeState::Running) {
            return NodeState::Running;  // currentIndex �״�� ����
        }
        else if (result == NodeState::Success) {
            m_CurrIndex = 0;  // �ʱ�ȭ
            return NodeState::Success;
        }
        else {      //Failure
            m_CurrIndex++;
        }
    }

    m_CurrIndex = 0;  // ��� �ڽ� ���� �� �ʱ�ȭ
    return NodeState::Failure;
}
