#include "CameraObject.h"
#include "CameraComponent.h"

CameraObject::CameraObject(EventDispatcher eventDispatcher, float width, float height) : GameObject(eventDispatcher)
{
	AddComponent<CameraComponent>();
	auto* camera = GetComponent<CameraComponent>();
	camera->m_Width = width;
	camera->m_Height = height;
}
