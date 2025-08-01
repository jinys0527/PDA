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

	//���콺 Ŭ�� �̺�Ʈ
	if (m_MousePrev.leftPressed == false)
	{
		if (m_Mouse.leftPressed == true)
		{
			m_EventDispatcher.Dispatch(EventType::MouseLeftClick, &m_Mouse);
		}
	}

	//��ư���� ȣ���ƴ��� Ȯ���ϱ� ���� �Ź� ��������
	m_EventDispatcher.Dispatch(EventType::Hovered, &m_Mouse);

	m_MousePrev = m_Mouse;
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

	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	{
		HandleMsgMouse(msg);
	}
	break;

	default:
		return false; // Unhandled message
	}

	return true;
}

void InputManager::HandleMsgMouse(const MSG& msg)
{
	int x = GetXFromLParam(msg.lParam);
	int y = GetYFromLParam(msg.lParam); // [���� ����]

	m_Mouse.pos = { x, y };

	if (msg.message == WM_LBUTTONDOWN)
	{
		m_Mouse.leftPressed = true;
		SetCapture(msg.hwnd);
	}
	else if (msg.message == WM_RBUTTONDOWN)
	{
		m_Mouse.rightPressed = true;
		SetCapture(msg.hwnd);
	}
	else if (msg.message == WM_LBUTTONUP)
	{
		m_Mouse.leftPressed = false;
		ReleaseCapture();
	}
	else if (msg.message == WM_RBUTTONUP)
	{
		m_Mouse.rightPressed = false;
		ReleaseCapture();
	}

}
