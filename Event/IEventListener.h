#pragma once

enum class EventType
{
	//Input
	KeyDown,
	KeyUp,
	MouseLeftClick,
	MouseLeftClickHold,
	MouseLeftClickUp,
	MouseRightClick,
	MouseRightClickHold,
	MouseRightClickUp,

	//UI
	Hovered,
	Pressed,
	Released,
	Moved,
	Dragged,

	//Collision
	CollisionEnter,
	CollisionStay,
	CollisionExit,
	CollisionTrigger,

	//Game
	OnPlayerCollisonOccur, // �÷��̾� �浹 �÷��̾� �ǰ� �� ���� ���� �� üũ
	OnPlayerReinforcedCollisionOccur, // �÷��̾� �浹 �÷��̾� �ǰ� �� ���� ���� �� üũ
	OnPlayerHpChanged, // �÷��̾� ��¥ �ǰ�
	OnPlayerReinforcedBulletChanged,
	OnPlayerDeath, // �÷��̾� ����
	OnScoreChange,
	OnBossScene,
	OnPlayerAttack

};

class IEventListener
{
public:
	virtual ~IEventListener() = default;
	virtual void OnEvent(EventType type, const void* data) = 0;
};
