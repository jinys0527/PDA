#pragma once
#include "GameObject.h"
#include "RectTransformComponent.h"
#include "UIComponent.h"

class UIObject : public GameObject
{
public:
	UIObject(EventDispatcher& eventDispatcher);
	virtual ~UIObject();

private:
	UIComponent* m_UI = nullptr;
};

