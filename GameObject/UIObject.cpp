#include "UIObject.h"
#include "UIButtonComponent.h"

UIObject::UIObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	//임시로 버튼 컴포넌트 넣음
	m_UI = AddComponent<UIButtonComponent>();
	eventDispatcher.AddListener(EventType::MouseLeftClick, m_UI);
	eventDispatcher.AddListener(EventType::Hovered, m_UI);
}

UIObject::~UIObject()
{
	m_EventDispatcher.RemoveListener(EventType::MouseLeftClick, m_UI);
	m_EventDispatcher.RemoveListener(EventType::Hovered, m_UI);
}

