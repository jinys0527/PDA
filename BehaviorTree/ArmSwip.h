#pragma once
#include "SkillNode.h"
#include "Telegraph.h"
#include "GameObject.h"


class ArmSwip : public SkillNode
{
public:
	ArmSwip(std::string name) : SkillNode(name) {}

	NodeState Tick(BlackBoard& bb, float deltaTime) override;

private:
	void StartWarning(BlackBoard& bb) override;
	void EndWarning(BlackBoard& bb) override;
	void Reset() override;

	//������ ��� �ε����� ������ �ε���
	std::vector<int> m_MoveStartIndex;
	std::vector<int> m_TargetIndex;

	//��ġ�� ����
	std::vector<Math::Vector2F> m_MoveStartPos;
	std::vector<Math::Vector2F> m_MoveTargetPos;

	bool m_IsMoving = false;
	bool m_Forward = true;       // ó���� ��ǥ �������� �̵�
	bool m_HasReturned = false;  // ���� ���ƿ��� ����

	float m_MoveTimer = 0.f;
	float m_MoveDuration = 0.7f;

	std::shared_ptr<GameObject> m_CurrentAnimObj;

};

