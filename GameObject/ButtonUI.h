#pragma once
#include "GameObject.h"
#include "UIButtonComponent.h"

class ButtonUI : public GameObject
{
public:
	ButtonUI(EventDispatcher& eventDispatcher);
	virtual ~ButtonUI() = default;

private:
	UIButtonComponent* m_UI;
};

