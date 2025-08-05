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
            std::cout << m_name << " 값이 없음" << std::endl;
            return NodeState::Failure;
        }

        bool currentVal = *valOpt;

        if (currentVal)
        {
            // 현재 값이 true면 성공을 반환, 값은 아직 바꾸지 않음
            std::cout << m_name << ": true (성공)" << std::endl;
            std::cout << "==================================" << std::endl;
            bb.SetValue(m_name, false);
            return NodeState::Success;
        }
        else
        {
            // 현재 값이 false면 실패를 반환하고, 다음엔 true가 되도록 값을 반전
            bb.SetValue(m_name, true);  // 다음번 호출 때 성공하도록 반전
            std::cout << m_name << ": false (실패) -> true로 변경" << std::endl;
            std::cout << "==================================" << std::endl;
            return NodeState::Failure;
        }
    }

};

