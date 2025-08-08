#pragma once
#include "CompositeNode.h"

// ��� ���� ����
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

        // ��� �ڽ� ��尡 �Ϸ�Ǹ�(Success �Ǵ� Failure) Success ��ȯ
        // �ϳ��� Running �����̸� Running ��ȯ
        if (hasRunningChild)
        {
            return NodeState::Running;
        }

        return NodeState::Success;
    }
};

