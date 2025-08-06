#pragma once
#include "BTNode.h"

class SkillNode : public BTNode
{
public:
	SkillNode(std::string name) : BTNode(name) {}

	NodeState Tick(BlackBoard& bb, float deltaTime) override;

private:
	void StartWarning(BlackBoard& bb);
	void EndWarning(BlackBoard& bb);
	void Reset();

	float m_WarningTime = 3.f;
	float m_ElapsedTime = 0.f;

	bool m_HasStarted = false;
};

