#pragma once
#include "BTNode.h"

class PhaseChecker_2 : public BTNode
{
public:
	PhaseChecker_2(std::string name) : BTNode(name) {}

	NodeState Tick(BlackBoard& bb, float deltaTime) override;
};

