#pragma once
#include "BTNode.h"
#include "BlackBoard.h"

class TestNode : public BTNode
{
public:
	TestNode(std::string name) : BTNode(name) {}

    NodeState Tick(BlackBoard& bb) override
    {
        std::cout << "name: " << m_name << std::endl;

        auto valOpt = bb.GetValue<bool>(m_name);
        if (!valOpt.has_value())
        {
            std::cout << m_name << " ���� ����" << std::endl;
            return NodeState::Failure;
        }

        bool currentVal = *valOpt;

        if (currentVal)
        {
            // ���� ���� true�� ������ ��ȯ, ���� ���� �ٲ��� ����
            std::cout << m_name << ": true (����)" << std::endl;
            std::cout << "==================================" << std::endl;
            bb.SetValue(m_name, false);
            return NodeState::Success;
        }
        else
        {
            // ���� ���� false�� ���и� ��ȯ�ϰ�, ������ true�� �ǵ��� ���� ����
            bb.SetValue(m_name, true);  // ������ ȣ�� �� �����ϵ��� ����
            std::cout << m_name << ": false (����) -> true�� ����" << std::endl;
            std::cout << "==================================" << std::endl;
            return NodeState::Failure;
        }
    }

};

