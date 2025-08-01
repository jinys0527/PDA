#include "ButtonUI.h"
#include "Component.h"

ButtonUI::ButtonUI(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	m_UI = AddComponent<UIButtonComponent>();
}
