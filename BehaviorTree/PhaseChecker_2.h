#pragma once
#include "BTNode.h"
#include "AnimationUtils.h"

class PhaseChecker_2 : public BTNode
{
public:
	PhaseChecker_2(std::string name) : BTNode(name) {}

	NodeState Tick(BlackBoard& bb, float deltaTime) override;

private:
	bool m_PhaseChange = false;

	float m_targetY = 600.f;
	float m_moveSpeed = 200.f;

	std::shared_ptr<GameObject> m_Lazer_CCTV;

};

