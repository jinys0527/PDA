#pragma once
#include "BTNode.h"
#include "Telegraph.h"
#include "GameObject.h"


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
	float m_AnimTimer = 0.0f;

	bool m_HasStarted = false;
	bool m_Initialized = false;
	bool m_AnimPlaying = false;
	bool m_AttackStarted = false;

	std::vector<std::shared_ptr<Telegraph>> m_Telegraphs;
	std::vector<std::shared_ptr<GameObject>> m_Anims;

	std::vector<int> m_AttackRange;

};

