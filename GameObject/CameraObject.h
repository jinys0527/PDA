#pragma once
#include "GameObject.h"

class CameraComponent;

class CameraObject : public GameObject
{
public:
	CameraObject(EventDispatcher& eventDispatcher, float width, float height);
	virtual ~CameraObject() = default;

private:
	CameraComponent* m_CameraComp;
};

