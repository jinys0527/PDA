#include "pch.h"
#include "InputManager.h"
#include "EventDispatcher.h"
#include "Event.h"
#include <iostream>

InputManager::InputManager(EventDispatcher& dispatcher) : m_EventDispatcher(dispatcher)
{

}

void InputManager::Update()
{
	for (const auto& key : m_KeysDown)
	{
		if (!m_KeysDownPrev.contains(key))
		{
			Events::KeyEvent e{ key };
			m_EventDispatcher.Dispatch(EventType::KeyDown, &e);
		}
	}

	for (const auto& key : m_KeysDownPrev)
	{
		if (!m_KeysDown.contains(key))
		{
			Events::KeyEvent e{ key };
			m_EventDispatcher.Dispatch(EventType::KeyUp, &e);
		}
	}

	m_KeysDownPrev = m_KeysDown;
}

void InputManager::OnKeyDown(char key)
{
	m_KeysDown.insert(key);
}

void InputManager::OnKeyUp(char key)
{
	m_KeysDown.erase(key);
}

bool InputManager::IsKeyPressed(char key) const
{
	return m_KeysDown.contains(key);
}

bool InputManager::OnHandleMessage(const MSG& msg)
{
	switch (msg.message)
	{

	case WM_KEYDOWN:
	{
		OnKeyDown(static_cast<char>(msg.wParam));
	}
	break;

	case WM_KEYUP:
	{
		OnKeyUp(static_cast<char>(msg.wParam));
	}
	break;

	//case WM_MOUSEMOVE:
	//case WM_LBUTTONDOWN:
	//case WM_LBUTTONUP:
	//case WM_RBUTTONDOWN:
	//case WM_RBUTTONUP:
	//{
	//	HandleMsgMouse(msg);
	//}
	//break;

	default:
		return false; // Unhandled message
	}

	return true;
}
