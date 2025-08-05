#include "Inverter.h"

NodeState Inverter::Tick(BlackBoard& bb)
{
    NodeState result = m_Children->Tick(bb);

    switch (result) 
    {
    case NodeState::Success: return NodeState::Failure;
    case NodeState::Failure: return NodeState::Success;
    case NodeState::Running: return NodeState::Running;
    }

    return NodeState::Failure; // 혹시 모를 오류 처리
}

