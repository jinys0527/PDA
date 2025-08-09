#pragma once
#include "SkillNode.h"

class Lazer : public SkillNode
{
public:
	Lazer(std::string name) : SkillNode(name) {}

	NodeState Tick(BlackBoard& bb, float deltaTime) override;

private:
	void StartWarning(BlackBoard& bb);
	void EndWarning(BlackBoard& bb);
	void Reset();

	int m_StartTelIndex;
	int m_PrevLeft = -1;
	int m_PrevRight = -1;
	int m_minIndex = 0;
	int m_maxIndex = 0;

	int m_ActivateStep = 0;
	float m_ActivateTimer = 0.0f;

	bool m_IsActivating = false;
};

