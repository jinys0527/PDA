#pragma once
#include "SkillNode.h"
#include "Telegraph.h"
#include "GameObject.h"

class ArmSmash : public SkillNode
{
public:
	ArmSmash(std::string name) : SkillNode(name) {}

	NodeState Tick(BlackBoard& bb, float deltaTime) override;

private:
	void StartWarning(BlackBoard& bb);
	void EndWarning(BlackBoard& bb);
	void Reset();

	//텔레그래프 위치 관련
	int m_minIndex = 12;
	int m_maxIndex = 0;

	float m_WarningTime = 3.f;
	float m_ElapsedTime = 0.f;
	float m_AnimTimer = 0.0f;

	//이동 관련
	float m_MoveTimer = 0.0f;
	float m_MoveDuration = 0.7f;
	bool m_IsMoving = false;

	bool m_HasStarted = false;
	bool m_Initialized = false;
	bool m_AnimPlaying = false;
	bool m_AttackStarted = false;

	Math::Vector2F m_MoveStartPos = { 0,0 };
	Math::Vector2F m_MoveTargetPos = { 0,0 };

	std::vector<std::shared_ptr<Telegraph>> m_Telegraphs;
	std::vector<std::shared_ptr<GameObject>> m_Anims;

	std::vector<int> m_AttackRange;


};

