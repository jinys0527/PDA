#include "PhaseChecker_1.h"
#include "BlackBoard.h"

NodeState PhaseChecker_1::Tick(BlackBoard& bb, float deltaTime)
{
    int currPhase = bb.GetValue<int>("CurrPhase").value();
    float hp = bb.GetValue<float>("BossCurrHP").value();

    if (currPhase == 1)
        return NodeState::Success;

    if (hp >= 50.f)
    {
        bb.SetValue("CurrPhase", 1);
        return NodeState::Success;
    }

    return NodeState::Failure;
}