#pragma once
#include <unordered_set>
#include <windows.h>
#include "EventDispatcher.h"

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
private:
	std::unordered_set<char> m_KeysDown;			// ���� ����
	std::unordered_set<char> m_KeysDownPrev;		// ���� ������ ����
	EventDispatcher& m_EventDispatcher;			// ���� ����
};

