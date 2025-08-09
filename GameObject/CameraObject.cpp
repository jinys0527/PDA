#include "CameraObject.h"
#include "CameraComponent.h"

CameraObject::CameraObject(EventDispatcher& eventDispatcher, float width, float height) : GameObject(eventDispatcher)
{
	m_CameraComp = AddComponent<CameraComponent>(width, height);
	m_CameraComp->m_Width = width;
	m_CameraComp->m_Height = height;
}