#include "UIObject.h"
#include "UIButtonComponent.h"

UIObject::UIObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	//�ӽ÷� ��ư ������Ʈ ����
	m_UI = AddComponent<UIButtonComponent>();
}

UIObject::~UIObject()
{
}

