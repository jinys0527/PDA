#pragma once
#include <unordered_set>
#include <windows.h>
#include "EventDispatcher.h"
#include "Event.h"

inline int GetXFromLParam(LPARAM lp) { return (int)(short)(LOWORD(lp)); }
inline int GetYFromLParam(LPARAM lp) { return (int)(short)(HIWORD(lp)); }


class InputManager
{
public:
	InputManager(EventDispatcher& dispatcher);
	~InputManager() = default;
	void Update();
	void OnKeyDown(char key);
	void OnKeyUp(char key);
	bool IsKeyPressed(char key) const;
	bool OnHandleMessage(const MSG& msg);
	void HandleMsgMouse(const MSG& msg);

private:
	std::unordered_set<char> m_KeysDown;			// ���� ����
	std::unordered_set<char> m_KeysDownPrev;		// ���� ������ ����

	Events::MouseState m_Mouse;
	Events::MouseState m_MousePrev;

	EventDispatcher& m_EventDispatcher;				// ���� ����
};

