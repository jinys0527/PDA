#pragma once
#include "BTNode.h"

class BossSkillNode : public BTNode
{
	BossSkillNode(std::string name) : BTNode(name) {}

	NodeState Tick(BlackBoard& bb) override;
};

