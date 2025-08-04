#pragma once
#include "UIComponent.h"
#include <wrl/client.h>
#include <d2d1_1.h>
#include "SimpleMathHelper.h"

class D2DRenderer;

enum class ImagePivotPreset
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,
	Center
};

class UIImageComponent : public UIComponent
{
public:
	static constexpr const char* StaticTypeName = "UIImageComponent";
	const char* GetTypeName() const override { return StaticTypeName; }

	virtual ~UIImageComponent() = default;
	void SetBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap);
	void SetUV(const D2D1_RECT_F& sourceRect);
	void Render(D2DRenderer* renderer);

	void SetPivotPreset(ImagePivotPreset spp, const D2D1_SIZE_F& size);
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> GetTexture() const;
	const Math::Vector2F& GetPivot() const
	{
		return m_Pivot;
	}

	float GetOpacity()
	{
		return m_Opacity;
	}

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;
private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_Bitmap;
	D2D1_RECT_F m_SourceRect = {};
	Math::Vector2F m_Pivot;
	float m_Opacity = 1.0f;
};

REGISTER_COMPONENT(UIImageComponent);