#pragma once
#include "BTNode.h"
#include "AnimationUtils.h"

class PhaseChecker_3 : public BTNode
{
public:
	PhaseChecker_3(std::string name) : BTNode(name) {}

	NodeState Tick(BlackBoard& bb, float deltaTime) override;

private:
	bool m_PhaseChange = false;

	std::shared_ptr<GameObject> m_Boss_Main;
	std::shared_ptr<GameObject> m_Boss_Arm_L;
	std::shared_ptr<GameObject> m_Boss_Arm_R;
};
