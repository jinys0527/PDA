#pragma once
#include "BTNode.h"

class BossCoolDown : public BTNode
{
	BossCoolDown(std::string name) : BTNode(name) {}

	NodeState Tick(BlackBoard& bb) override;
};

