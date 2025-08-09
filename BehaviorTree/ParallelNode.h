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
        bool hasFailureChild = false;

        for (auto& child : m_Children)
        {
            NodeState state = child->Tick(bb, deltaTime);
            if (state == NodeState::Running)
            {
                hasRunningChild = true;
            }
            else if (state == NodeState::Failure)
            {
                hasFailureChild = true;
            }
        }

        if (hasFailureChild)
            return NodeState::Failure;

        if (hasRunningChild)
            return NodeState::Running;

        return NodeState::Success;
    }
};

