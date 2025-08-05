#include "Inverter.h"

NodeState Inverter::Tick()
{
    NodeState result = m_Children->Tick();

    switch (result) 
    {
    case NodeState::Success: return NodeState::Failure;
    case NodeState::Failure: return NodeState::Success;
    case NodeState::Running: return NodeState::Running;
    }

    return NodeState::Failure; // Ȥ�� �� ���� ó��
}

