#pragma once
#include "GameObject.h"

class CameraObject : public GameObject
{
public:
	CameraObject(EventDispatcher eventDispatcher, float width, float height);
	virtual ~CameraObject() = default;
};

