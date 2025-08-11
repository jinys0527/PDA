#pragma once
#include "SkillNode.h"
#include "Telegraph.h"
#include "GameObject.h"

class ArmStretch : public SkillNode
{
public:
	ArmStretch(std::string name) : SkillNode(name) {}

	NodeState Tick(BlackBoard& bb, float deltaTime) override;

private:
	void StartWarning(BlackBoard& bb) override;
	void EndWarning(BlackBoard& bb) override;
	void Reset() override;

	//�ڷ��׷��� ��ġ ����
	int m_minIndex = 15;
	int m_maxIndex = 0;

	//�̵� ����
	float m_MoveTimer = 0.0f;
	float m_MoveDuration = 0.7f;

	bool m_IsMovingToStartPos = false;
	//�ݶ��̴�
	bool m_IsMoving = false;

	//��������Ʈ ��ü? ��ü �̵�
	float m_MoveToStartPosTimer = 0.0f;
	float m_MoveToStartPosDuration = 1.0f;
	Math::Vector2F m_MoveFromPos = { 0, 0 };

	//�ݶ��̴� ����
	Math::Vector2F m_MoveStartPos = { 0,0 };
	Math::Vector2F m_MoveTargetPos = { 0,0 };

	std::shared_ptr<GameObject> m_CurrentAnimObj;

};

