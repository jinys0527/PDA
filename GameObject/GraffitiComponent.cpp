#include "GraffitiComponent.h"
#include "GameObject.h"
#include "Event.h"
#include "TransformComponent.h"
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
	std::cout << "m_IsHovered: " << m_IsHovered << std::endl;
	std::cout << "m_IsClicked: " << m_IsClicked << std::endl;

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
		}
	}
}

void GraffitiComponent::IsHovered(POINT mousePos)
{
	mousePos.y = 1080 - mousePos.y;

	auto objPos = m_Owner->GetComponent<TransformComponent>()->GetPosition();
	auto objSize = m_Owner->GetComponent<SpriteRenderer>()->GetTexture()->GetSize();
	auto objPivot = m_Owner->GetComponent<SpriteRenderer>()->GetPivot();

	Math::Vector2F topLeft;
	topLeft.x = objPos.x - objPivot.x;
	topLeft.y = objPos.y - objPivot.y;

	if (mousePos.x >= topLeft.x && mousePos.x <= (topLeft.x + objSize.width) &&
		mousePos.y >= topLeft.y && mousePos.y <= (topLeft.y + objSize.height))
	{
		m_IsHovered = true;
	}
	else
	{
		m_IsHovered = false;
	}
}


