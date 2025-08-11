#pragma once
#include "CompositeNode.h"
#include <iostream>

class ParallelNode : public CompositeNode
{
public:
    ParallelNode(std::string name) : CompositeNode(name)
    {
        m_ChildStates.resize(m_Children.size(), NodeState::Running);
    }

    // �ڽ� ��尡 �ٲ�� ���µ� ���缭 ��������
    void SyncChildStates()
    {
        if (m_ChildStates.size() != m_Children.size())
            m_ChildStates.resize(m_Children.size(), NodeState::Running);
    }

    void Reset()
    {
        for (auto& state : m_ChildStates)
            state = NodeState::Running;

        for (auto& child : m_Children)
        {
            child->Reset();
        }
    }

    NodeState Tick(BlackBoard& bb, float deltaTime) override
    {
        SyncChildStates();

        bool allSuccess = true;
        bool hasFailure = false;

        for (size_t i = 0; i < m_Children.size(); ++i)
        {
            // �̹� �Ϸ�� �ڽ� ���� �ٽ� Tick �� ��
            if (m_ChildStates[i] == NodeState::Success)
                continue;

            if (m_ChildStates[i] == NodeState::Failure)
            {
                hasFailure = true;
                continue;
            }

            m_ChildStates[i] = m_Children[i]->Tick(bb, deltaTime);

            if (m_ChildStates[i] == NodeState::Failure)
                hasFailure = true;
            if (m_ChildStates[i] != NodeState::Success)
                allSuccess = false;
        }

        if (hasFailure)
        {
            // std::cout << "Failure: " << m_Name << std::endl;
            return NodeState::Failure;
        }

        if (allSuccess)
        {
            // std::cout << "Success: " << m_Name << std::endl;
            return NodeState::Success;
        }

        // std::cout << "Running: " << m_Name << std::endl;
        return NodeState::Running;
    }

private:
    std::vector<NodeState> m_ChildStates;
};
