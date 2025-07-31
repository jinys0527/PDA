#include "UIObject.h"
#include "UIComponent.h"

UIObject::UIObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	m_UI = AddComponent<UIComponent>();
	eventDispatcher.AddListener(EventType::MouseLeftClick, m_UI);
	eventDispatcher.AddListener(EventType::Hovered, m_UI);
}

UIObject::~UIObject()
{
	m_EventDispatcher.RemoveListener(EventType::MouseLeftClick, m_UI);
	m_EventDispatcher.RemoveListener(EventType::Hovered, m_UI);
}

