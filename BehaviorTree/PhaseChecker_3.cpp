#include "PhaseChecker_3.h"
#include "BlackBoard.h"

NodeState PhaseChecker_3::Tick(BlackBoard& bb, float deltaTime)
{
    int currPhase = bb.GetValue<int>("CurrPhase").value();
    float hp = bb.GetValue<float>("BossCurrHP").value();

    if (currPhase == 3)
        return NodeState::Success;

    if (hp < 50.f)
    {
        bb.SetValue("CurrPhase", 3);
        return NodeState::Success;
    }

    return NodeState::Failure;
}