#pragma once
#include "BTNode.h"
#include "BlackBoard.h"

class TestNode : public BTNode
{
public:
	TestNode(std::string name) : BTNode(name) {}

    NodeState Tick(BlackBoard& bb, float deltaTime) override
    {
        std::cout << "name: " << m_Name << std::endl;

        auto valOpt = bb.GetValue<bool>(m_Name);
        if (!valOpt.has_value())
        {
            std::cout << m_Name << " ���� ����" << std::endl;
            return NodeState::Failure;
        }

        bool currentVal = *valOpt;

        if (currentVal)
        {
            // ���� ���� true�� ������ ��ȯ, ���� ���� �ٲ��� ����
            std::cout << m_Name << ": true (����)" << std::endl;
            std::cout << "==================================" << std::endl;
            bb.SetValue(m_Name, false);
            return NodeState::Success;
        }
        else
        {
            // ���� ���� false�� ���и� ��ȯ�ϰ�, ������ true�� �ǵ��� ���� ����
            bb.SetValue(m_Name, true);  // ������ ȣ�� �� �����ϵ��� ����
            std::cout << m_Name << ": false (����) -> true�� ����" << std::endl;
            std::cout << "==================================" << std::endl;
            return NodeState::Failure;
        }
    }

};

