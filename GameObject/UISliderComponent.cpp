#include "UISliderComponent.h"


UISliderComponent::UISliderComponent()
{
}

void UISliderComponent::Update(float deltaTime)
{
	if (m_IsDirty)
	{
		UpdateFillImage(); //fill 이미지 갱신
		m_IsDirty = false;
	}
}

void UISliderComponent::OnEvent(EventType type, const void* data)
{
	auto mouseData = static_cast<const Events::MouseState*>(data);
	auto rect = m_Fill->GetUV();
	float percentage;
	switch (type)
	{
	case EventType::Pressed:
		m_IsDragging = true;
		m_CurrentMousePos = mouseData->pos;
		break;
	case EventType::Dragged:
		if(m_IsDragging)
		{
			m_CurrentMousePos = mouseData->pos;
		}
		break;
	case EventType::Released:
		percentage = std::clamp((m_CurrentMousePos.x - m_MinX) / m_Width, 0.0f, 1.0f);
		SetValue(percentage);			// 여기서 자동으로 OnValueChanged 호출
		m_IsDragging = false;
		break;
	}
}

void UISliderComponent::Serialize(nlohmann::json& j) const
{
}

void UISliderComponent::Deserialize(const nlohmann::json& j)
{
}

void UISliderComponent::UpdateFillImage()
{
	auto rect = m_Fill->GetUV();
	float width = rect.right - rect.left;	
	float height = rect.bottom - rect.top;

	switch (m_Direction)
	{
	case FillDirection::LeftToRight:
		rect.right = rect.left + width * m_Value;
		break;
	case FillDirection::RightToLeft:
		rect.left = rect.right - width * m_Value;
		break;
	case FillDirection::BottomToTop:
		rect.top = rect.bottom - height * m_Value;
		break;
	case FillDirection::TopToBottom:
		rect.bottom = rect.top + height * m_Value;
		break;
	}
	m_Fill->SetUV(rect);
}
