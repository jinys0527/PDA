#pragma once

enum class EventType
{
	//Input
	KeyDown,
	KeyUp,
	MouseLeftClick,
	MouseRightClick,

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

	//Game
	OnPlayerCollisonOccur, // �÷��̾� �浹 �÷��̾� �ǰ� �� ���� ���� �� üũ
	OnPlayerHit, // �÷��̾� ��¥ �ǰ�
	OnPlayerDeath, // �÷��̾� ����
	OnScoreChange,
	OnBossScene

};

class IEventListener
{
public:
	virtual ~IEventListener() = default;
	virtual void OnEvent(EventType type, const void* data) = 0;
};
