#include "UIButtonComponent.h"
#include "iostream"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "UIImageComponent.h"

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

UIButtonComponent::~UIButtonComponent()
{
	m_Owner->GetEventDispatcher().RemoveListener(EventType::Hovered, this);
	m_Owner->GetEventDispatcher().RemoveListener(EventType::MouseLeftClick, this);
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
		//std::cout << "호버호버" << std::endl;
	}
	//std::cout << m_FSM.GetCurrentState() << std::endl;



}

void UIButtonComponent::OnEvent(EventType type, const void* data)
{
	//마우스 위치 받기
	if (type == EventType::Hovered)
	{
		auto mouseData = static_cast<const Events::MouseState*>(data);
		IsHovered(mouseData->pos);
		if (m_IsHovered)
		{
			if (m_FSM.GetCurrentState() == "None")
			{
				m_FSM.Trigger("NoneToHover");
			}
		}
		else if (!m_IsHovered && m_FSM.GetCurrentState() == "Hover")
		{
			m_FSM.Trigger("HoverToNone");
		}

	}

	//아래는 버튼UI가 될 듯
	if (type == EventType::MouseLeftClick)
	{
		if (m_IsHovered)
		{
			auto mouseData = static_cast<const Events::MouseState*>(data);
			//std::cout << mouseData->pos.x << " " << mouseData->pos.y << "에서 클릭됨 \n";
			m_IsClicked = true;
			m_FSM.Trigger("HoverToClick");

			m_FSM.Trigger("ClickToHover");
			m_IsClicked = false;

		}
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

	std::cout << mousePos.x << " " << mousePos.y << "에 위치함 \n";


	auto objPos = m_Owner->GetComponent<TransformComponent>()->GetPosition();
	auto objSize = m_Owner->GetComponent<UIImageComponent>()->GetTexture()->GetSize();
	auto objPivot = m_Owner->GetComponent<UIImageComponent>()->GetPivot();

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

