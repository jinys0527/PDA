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

	float m_fadeSpeed = 1.0f; 
	int m_Back2FadeDirection = 1;

	int m_PrintState = 3;

	float m_targetX = 1000.f;
	float m_moveSpeed = 300.f;

	std::shared_ptr<GameObject> m_Lazer_CCTV;

	std::shared_ptr<GameObject> m_Back_0;
	std::shared_ptr<GameObject> m_Back_1;
	std::shared_ptr<GameObject> m_Back_2;
	std::shared_ptr<GameObject> m_Back_3;
	std::shared_ptr<GameObject> m_Back_4;

};

