#include "UIComponent.h"
#include "Event.h"
#include "iostream"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"

void UIComponent::Update(float deltaTime)
{
	if (m_IsHovered)
	{
		std::cout << "호버호버" << std::endl;
	}
}

void UIComponent::OnEvent(EventType type, const void* data)
{
	//아래는 버튼UI가 될 듯
	if (type == EventType::MouseLeftClick)
	{
		auto mouseData = static_cast<const Events::MouseState*>(data);
		//std::cout << mouseData->pos.x << " " << mouseData->pos.y << "에서 클릭됨 \n";

	}

	//마우스 위치 받기
	if (type == EventType::Hovered)
	{
		auto mouseData = static_cast<const Events::MouseState*>(data);
		IsHovered(mouseData->pos);
	}


}

void UIComponent::Serialize(nlohmann::json& j) const
{
}

void UIComponent::Deserialize(const nlohmann::json& j)
{
}

void UIComponent::IsHovered(POINT mousePos)
{
	mousePos.y = 1080 - mousePos.y;

	std::cout << mousePos.x << " " << mousePos.y << "에 위치함 \n";


	auto objPos = m_Owner->GetComponent<TransformComponent>()->GetPosition();
	auto objSize = m_Owner->GetComponent<SpriteRenderer>()->GetTexture()->GetSize();
	auto objPivot = m_Owner->GetComponent<TransformComponent>()->GetPivotPoint();

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
