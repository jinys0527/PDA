#include "TestListener.h"
#include <iostream>
#include "Event.h"

void TestListener::OnEvent(EventType type, const void* data)
{
	switch (type)
	{
	case EventType::KeyDown:
	{
		auto keyEvent = static_cast<const Events::KeyEvent*>(data);
		std::cout << "KeyDown �̺�Ʈ ����: " << keyEvent->key << std::endl;
		break;
	}
	case EventType::KeyUp:
	{
		auto keyEvent = static_cast<const Events::KeyEvent*>(data);
		std::cout << "KeyUp �̺�Ʈ ����: " << keyEvent->key << std::endl;
		break;
	}
	case EventType::MouseClick:
		break;
	case EventType::Pressed:
		break;
	case EventType::Moved:
		break;
	default:
		break;
	}
}
