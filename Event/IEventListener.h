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


	//Collision
	CollisionEnter,
	CollisionStay,
	CollisionExit,

	//Game
	OnPlayerCollisonOccur, // 플레이어 충돌 플레이어 피격 전 무적 판정 등 체크
	OnPlayerHit, // 플레이어 진짜 피격
	OnPlayerDeath, // 플레이어 죽음

};

class IEventListener
{
public:
	virtual ~IEventListener() = default;
	virtual void OnEvent(EventType type, const void* data) = 0;
};
