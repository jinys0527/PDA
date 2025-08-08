#pragma once
#include "CompositeNode.h"

// 노드 연속 실행
class ParallelNode : public CompositeNode
{
public:
	ParallelNode(std::string name) : CompositeNode(name) {}

    NodeState Tick(BlackBoard& bb, float deltaTime) override
    {
        bool hasRunningChild = false;
        for (auto& child : m_Children)
        {
            NodeState state = child->Tick(bb, deltaTime);
            if (state == NodeState::Running)
            {
                hasRunningChild = true;
            }
        }

        // 모든 자식 노드가 완료되면(Success 또는 Failure) Success 반환
        // 하나라도 Running 상태이면 Running 반환
        if (hasRunningChild)
        {
            return NodeState::Running;
        }

        return NodeState::Success;
    }
};

