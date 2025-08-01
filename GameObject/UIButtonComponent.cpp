#include "UIButtonComponent.h"
#include "iostream"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"

UIButtonComponent::UIButtonComponent()
{
	State noneState{
		[]() {},
		[](float dt) {},
		[]() {}
	};

	State hoverState{
		[]() {},
		[](float dt) {},
		[]() {}
	};

	State clickState{
		[]() {},
		[](float dt) {},
		[]() {}
	};

	m_FSM.AddState("None", noneState);
	m_FSM.AddState("Hover", hoverState);
	m_FSM.AddState("Click", clickState);

	m_FSM.AddTransition("None", "Hover", "NoneToHover");
	m_FSM.AddTransition("Hover", "Click", "HoverToClick");
	m_FSM.AddTransition("Click", "Hover", "ClickToHover");
	m_FSM.AddTransition("Hover", "None", "HoverToNone");

	m_FSM.SetInitialState("None");


}

void UIButtonComponent::Start()
{
	m_Owner->GetEventDispatcher().AddListener(EventType::Hovered, this);
	m_Owner->GetEventDispatcher().AddListener(EventType::MouseLeftClick, this);

}

void UIButtonComponent::SetOnClick(std::function<void()> callback)
{

}

void UIButtonComponent::Render(D2DRenderer* renderer)
{

}

void UIButtonComponent::Update(float deltaTime)
{
	if (m_IsHovered)
	{
		//std::cout << "ȣ��ȣ��" << std::endl;
	}

}

void UIButtonComponent::OnEvent(EventType type, const void* data)
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

void UIButtonComponent::Serialize(nlohmann::json& j) const
{
}

void UIButtonComponent::Deserialize(const nlohmann::json& j)
{
}

void UIButtonComponent::IsHovered(POINT mousePos)
{
	mousePos.y = 1080 - mousePos.y;

	//std::cout << mousePos.x << " " << mousePos.y << "�� ��ġ�� \n";


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

