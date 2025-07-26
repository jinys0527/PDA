#include "UITextComponent.h"

void UITextComponent::SetText(const std::wstring& text)
{
	m_Text = text;
}

void UITextComponent::SetFontSize(float size)
{
	m_FontSize = size;
}

void UITextComponent::SetColor(const D2D1_COLOR_F& color)
{
	m_Color = color;
}

void UITextComponent::Render(D2DRenderer* renderer)
{
	
}

void UITextComponent::Serialize(nlohmann::json& j) const
{
}

void UITextComponent::Deserialize(const nlohmann::json& j)
{
}
