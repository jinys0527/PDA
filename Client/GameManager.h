#pragma once

#include "FSM.h"

enum class DeathReason {
	Obstacle1,
	Obstacle2,
	Obstacle3,
	BossAttack1,
	BossAttack2,
	BOssAttack3
};

class GameManager
{
public:
	GameManager() = default;
	~GameManager() = default;
private:
	int m_playerHp = 3;
	int m_playerStrongAttack = 3;

	int score = 0;
	int hitCount = 0;

	float scrollSpeed = 0;

	int mapTotalLength = 0;// ���߿� ���� ���� �ϰų� �� ���൵ �����ֱ� ���� �� ���� ����
	int mapPlayedLength = 0;

	// �÷��̾� ��ġ�� ������ ������ �߰��� ���ص� �ǰ���?

	FSM m_Fsm;
};

