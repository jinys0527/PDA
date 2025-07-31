#include "UIObject.h"
#include "UIButtonComponent.h"

UIObject::UIObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	//�ӽ÷� ��ư ������Ʈ ����
	m_UI = AddComponent<UIButtonComponent>();
	eventDispatcher.AddListener(EventType::MouseLeftClick, m_UI);
	eventDispatcher.AddListener(EventType::Hovered, m_UI);
}

UIObject::~UIObject()
{
	m_EventDispatcher.RemoveListener(EventType::MouseLeftClick, m_UI);
	m_EventDispatcher.RemoveListener(EventType::Hovered, m_UI);
}

