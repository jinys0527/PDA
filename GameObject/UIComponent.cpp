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
		std::cout << "ȣ��ȣ��" << std::endl;
	}
}

void UIComponent::OnEvent(EventType type, const void* data)
{
	//�Ʒ��� ��ưUI�� �� ��
	if (type == EventType::MouseLeftClick)
	{
		auto mouseData = static_cast<const Events::MouseState*>(data);
		//std::cout << mouseData->pos.x << " " << mouseData->pos.y << "���� Ŭ���� \n";

	}

	//���콺 ��ġ �ޱ�
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

	std::cout << mousePos.x << " " << mousePos.y << "�� ��ġ�� \n";


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
