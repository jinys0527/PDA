#include "Inverter.h"

NodeState Inverter::Tick(BlackBoard& bb, float deltaTime)
{
    NodeState result = m_Children->Tick(bb, deltaTime);

    switch (result) 
    {
    case NodeState::Success: return NodeState::Failure;
    case NodeState::Failure: return NodeState::Success;
    case NodeState::Running: return NodeState::Running;
    }

    return NodeState::Failure; // Ȥ�� �� ���� ó��
}

