#include "SpriteRenderer.h"

void SpriteRenderer::SetPivotPreset(SpritePivotPreset spp, const D2D1_SIZE_F& size)
{
	switch (spp)
	{
	case SpritePivotPreset::TopLeft:
		m_Pivot = { 0.0f, 0.0f };
		break;
	case SpritePivotPreset::TopRight:
		m_Pivot = { size.width, 0.0f };
		break;
	case SpritePivotPreset::Center:
		m_Pivot = { size.width * 0.5f, size.height * 0.5f };
		break;
	case SpritePivotPreset::BottomLeft:
		m_Pivot = { 0.0f, size.height };
		break;
	case SpritePivotPreset::BottomRight:
		m_Pivot = { size.width, size.height };
		break;
	}
}

SpriteRenderer::SpriteRenderer() : m_FlipX(false), m_FlipY(false)
{
}

void SpriteRenderer::Update(float deltaTime)
{
}

void SpriteRenderer::OnEvent(EventType type, const void* data)
{
}

void SpriteRenderer::Serialize(nlohmann::json& j) const
{
}

void SpriteRenderer::Deserialize(const nlohmann::json& j)
{
}

void SpriteRenderer::SetTexture(Microsoft::WRL::ComPtr<ID2D1Bitmap1> texture)
{
	m_Sprite = texture;
}

Microsoft::WRL::ComPtr<ID2D1Bitmap1> SpriteRenderer::GetTexture() const
{
	return m_Sprite;
}

void SpriteRenderer::SetFlipX(bool flipX)
{
	m_FlipX = flipX;
}

bool SpriteRenderer::GetFlipX() const
{
	return m_FlipX;
}

void SpriteRenderer::SetFlipY(bool flipY)
{
	m_FlipY = flipY;
}

bool SpriteRenderer::GetFlipY() const
{
	return m_FlipY;
}


