#include "UIImageComponent.h"

void UIImageComponent::SetBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap)
{
	m_Bitmap = bitmap;
}

void UIImageComponent::SetUV(const D2D1_RECT_F& sourceRect)
{
	m_SourceRect = sourceRect;
}

void UIImageComponent::Render(D2DRenderer* renderer)
{

}

void UIImageComponent::Serialize(nlohmann::json& j) const
{
}

void UIImageComponent::Deserialize(const nlohmann::json& j)
{
}
