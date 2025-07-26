#pragma once
#include "Component.h"
#include "wrl/client.h"
#include "SimpleMathHelper.h"
#include <d2d1_1.h>

enum class SpritePivotPreset
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	Center
};

class SpriteRenderer : public Component
{
	using Vec2F = Math::Vector2F;
public:
	SpriteRenderer();
	virtual ~SpriteRenderer() = default;

	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
	std::string GetTypeName() override { return "SpriteRenderer"; }

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;

	void SetTexture(Microsoft::WRL::ComPtr<ID2D1Bitmap1> texture);
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> GetTexture() const;

	void SetFlipX(bool flipX);
	bool GetFlipX() const;

	void SetFlipY(bool flipY);
	bool GetFlipY() const;

	const Vec2F& GetPivot() const
	{
		return m_Pivot;
	}

	void SetPivotPreset(SpritePivotPreset spp, const D2D1_SIZE_F& size);

private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_Sprite;
	bool m_FlipX;
	bool m_FlipY;
	Vec2F m_Pivot;
};