#pragma once

#include "FSM.h"
#include "EventDispatcher.h"

//enum class DeathReason {
//	Obstacle1,
//	Obstacle2,
//	Obstacle3,
//	BossAttack1,
//	BossAttack2,
//	BOssAttack3
//};

class GameManager : public IEventListener
{
public:
	GameManager(EventDispatcher& eventDispatcher);
	~GameManager();

	void Reset();

	void OnEvent(EventType type, const void* data);

	int m_playerHp = 3;
	int m_playerReinforcedAttack = 3;
	float m_playerXLoc = -1000;

	int m_score = 0;
	int m_hitCount = 0;

	float m_scrollSpeed = 0;

private:

	int m_initialHp = 3;
	int m_initialReinforcedAttack = 3;

	int m_prevHp = 3;



	int m_mapTotalLength = 0;// ���߿� ���� ���� �ϰų� �� ���൵ �����ֱ� ���� �� ���� ����
	int m_mapPlayedLength = 0;

	// �÷��̾� ��ġ�� ������ ������ �߰��� ���ص� �ǰ���?

	FSM m_Fsm; // Fsm ���� �����ε� ���߿� ����ҵ�

	EventDispatcher& m_EventDispatcher;
};

