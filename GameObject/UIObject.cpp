#include "UIObject.h"
#include "UIButtonComponent.h"

UIObject::UIObject(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	//임시로 버튼 컴포넌트 넣음
	m_UI = AddComponent<UIButtonComponent>();
}

UIObject::~UIObject()
{
}

