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

	int mapTotalLength = 0;// 나중에 게임 정산 하거나 맵 진행도 보여주기 위한 맵 길이 저장
	int mapPlayedLength = 0;

	// 플레이어 위치를 저장할 포인터 추가는 안해도 되겠죠?

	FSM m_Fsm;
};

