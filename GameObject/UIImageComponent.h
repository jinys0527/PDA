#pragma once
#include "UIComponent.h"
#include <wrl/client.h>
#include <d2d1_1.h>

class D2DRenderer;

class UIImageComponent : public UIComponent
{
public:
	virtual ~UIImageComponent() = default;
	void SetBitmap(Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap);
	void SetUV(const D2D1_RECT_F& sourceRect);
	void Render(D2DRenderer* renderer);

	std::string GetTypeName() override { return "UIImageComponent"; }

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;
private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_Bitmap;
	D2D1_RECT_F m_SourceRect = {};
};

