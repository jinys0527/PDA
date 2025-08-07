#include "PhaseChecker.h"
#include "BlackBoard.h"

NodeState PhaseChecker::Tick(BlackBoard& bb, float deltaTime)
{
    int currPhase = bb.GetValue<int>("CurrPhase").value();
    float hp = bb.GetValue<float>("BossCurrHP").value();

    if (hp >= 50.f)
    {
        if (currPhase != 1)
        {
            bb.SetValue("CurrPhase", 1);
            std::cout << "=============1페 진입==============\n";
            return NodeState::Success;
        }
        else
        {
            return NodeState::Failure;
        }
    }

    if (hp < 50.f)
    {
        if (currPhase != 2)
        {
            bb.SetValue("CurrPhase", 2);
            std::cout << "=============2페 진입==============\n";
            return NodeState::Success;
        }
        else
        {
            // 이미 2페라면 반복 실행 방지
            return NodeState::Failure;
        }
    }

    return NodeState::Failure;
}