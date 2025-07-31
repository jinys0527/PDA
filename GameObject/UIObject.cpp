#include "UIObject.h"
#include "UIComponent.h"

UIObject::UIObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	m_UI = AddComponent<UIComponent>();
	eventDispatcher.AddListener(EventType::MouseLeftClick, m_UI);
}

UIObject::~UIObject()
{
	m_EventDispatcher.RemoveListener(EventType::MouseLeftClick, m_UI);
}

