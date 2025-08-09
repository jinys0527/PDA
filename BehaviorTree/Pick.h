#pragma once
#include "SkillNode.h"
#include "Telegraph.h"
#include "GameObject.h"

class Pick : public SkillNode
{
public:
	Pick(std::string name) : SkillNode(name) {}

	NodeState Tick(BlackBoard& bb, float deltaTime) override;

private:
	void StartWarning(BlackBoard& bb) override;
	void EndWarning(BlackBoard& bb) override;
	void Reset() override;


};

