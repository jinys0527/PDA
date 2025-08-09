#include "UIButtonComponent.h"
#include "iostream"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "UIImageComponent.h"
#include "UIUtils.h"

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
	m_Owner->GetEventDispatcher().AddListener(EventType::Pressed, this);

}

UIButtonComponent::~UIButtonComponent()
{
	//m_Owner->GetEventDispatcher().RemoveListener(EventType::Hovered, this);
	//m_Owner->GetEventDispatcher().RemoveListener(EventType::Pressed, this);
}


void UIButtonComponent::Update(float deltaTime)
{
}

void UIButtonComponent::OnEvent(EventType type, const void* data)
{
	//���콺 ��ġ �ޱ�
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

	//�Ʒ��� ��ưUI�� �� ��
	if (type == EventType::Pressed)
	{
		if (m_IsHovered)
		{
			auto mouseData = static_cast<const Events::MouseState*>(data);
			std::cout << mouseData->pos.x << " " << mouseData->pos.y << "���� Ŭ���� \n";
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
	auto rectTransform = m_Owner->GetComponent<RectTransformComponent>();
	auto image = m_Owner->GetComponent<UIImageComponent>();

	Math::Vector2F size = rectTransform->GetSize(); // ���� ������ ũ��
	D2D1_POINT_2F pivot = image->GetPivot();       // 0~1 ���� ����
	Math::Vector2F position = rectTransform->GetPosition(); // ��Ŀ ���� ��ġ

	m_IsHovered = IsPointInUIRect(position, size, pivot, mousePos);
}