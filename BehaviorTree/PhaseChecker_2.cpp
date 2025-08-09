#include "PhaseChecker_2.h"
#include "BlackBoard.h"

NodeState PhaseChecker_2::Tick(BlackBoard& bb, float deltaTime)
{
    int currPhase = bb.GetValue<int>("CurrPhase").value();
    float hp = bb.GetValue<float>("BossCurrHP").value();
    bool isPhase3 = bb.GetValue<bool>("3Phase").value();

    if (currPhase == 2)
        return NodeState::Success;

    if (hp < 50.f && !isPhase3)
    {
        bb.SetValue("CurrPhase", 2);
        return NodeState::Success;
    }

    return NodeState::Failure;
}