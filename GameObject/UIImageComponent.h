#pragma once
#include "UIComponent.h"
#include <wrl/client.h>
#include <d2d1_1.h>

class D2DRenderer;

class UIImageComponent : public UIComponent
{
public:
	static constexpr const char* StaticTypeName = "UIImageComponent";
	const char* GetTypeName() const override { return StaticTypeName; }

	virtual ~UIImageComponent() = default;
	void SetBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap);
	void SetUV(const D2D1_RECT_F& sourceRect);
	void Render(D2DRenderer* renderer);

	D2D1_RECT_F GetUV()
	{
		return m_SourceRect;
	}

	void SetOpacity(float opacity)
	{
		m_Opacity = std::clamp(opacity, 0.0f, 1.0f);
	}

	const float& GetOpacity() const { return m_Opacity; }

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;
private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_Bitmap;
	D2D1_RECT_F m_SourceRect = {};
	float m_Opacity = 1.0f;
};

REGISTER_COMPONENT(UIImageComponent);