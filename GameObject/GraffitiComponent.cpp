#include "GraffitiComponent.h"
#include "GameObject.h"
#include "Event.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "SpriteRenderer.h"
#include "iostream"

GraffitiComponent::GraffitiComponent()
{

}

GraffitiComponent::~GraffitiComponent()
{
	m_Owner->GetEventDispatcher().RemoveListener(EventType::Hovered, this);
	m_Owner->GetEventDispatcher().RemoveListener(EventType::MouseRightClick, this);

}

void GraffitiComponent::Start()
{
	m_Owner->GetEventDispatcher().AddListener(EventType::Hovered, this);
	m_Owner->GetEventDispatcher().AddListener(EventType::MouseRightClick, this);

}

void GraffitiComponent::Update(float deltatime)
{
	//std::cout << "m_IsHovered: " << m_IsHovered << std::endl;
	//std::cout << "m_IsClicked: " << m_IsClicked << std::endl;

}

void GraffitiComponent::OnEvent(EventType type, const void* data)
{
	auto mouseData = static_cast<const Events::MouseState*>(data);
	IsHovered(mouseData->pos);

	if (type == EventType::MouseRightClick)
	{
		if (m_IsHovered)
		{
			auto mouseData = static_cast<const Events::MouseState*>(data);
			//std::cout << mouseData->pos.x << " " << mouseData->pos.y << "¿¡¼­ Å¬¸¯µÊ \n";
			m_IsClicked = true;
			if (!m_IsFirst)
			{
				m_IsFirst = true;
				int one = 1;
				GetEventDispatcher().Dispatch(EventType::OnPlayerReinforcedCollisionOccur, (const void*)one);
			}
		}
	}
}

void GraffitiComponent::SetCameraObject(GameObject* cameraObject)
{
	m_CameraObject = cameraObject;
}

void GraffitiComponent::IsHovered(POINT mousePos)
{
	//mousePos.y = 1080 - mousePos.y;

	auto objPos = m_Owner->GetComponent<TransformComponent>()->GetPosition();
	auto objSize = m_Owner->GetComponent<SpriteRenderer>()->GetTexture()->GetSize();
	auto objPivot = m_Owner->GetComponent<SpriteRenderer>()->GetPivot();

	D2D1_POINT_2F topLeft;
	topLeft.x = objPos.x - objPivot.x;
	topLeft.y = objPos.y - objPivot.y;

	D2D1_POINT_2F mouse;
	mouse.x = mousePos.x;
	mouse.y = mousePos.y;

	D2D1::Matrix3x2F viewMatrix = m_CameraObject->GetComponent<CameraComponent>()->GetViewMatrix();
	viewMatrix.Invert();
	mouse = viewMatrix.TransformPoint(mouse);
	//std::cout << "x : " << mouse.x << " y : " << mouse.y << std::endl;

	if (mouse.x >= topLeft.x && mouse.x <= (topLeft.x + objSize.width) &&
		mouse.y >= topLeft.y && mouse.y <= (topLeft.y + objSize.height))
	{
		m_IsHovered = true;
	}
	else
	{
		m_IsHovered = false;
	}
}


