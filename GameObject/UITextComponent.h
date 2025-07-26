#pragma once
#include "UIComponent.h"
#include <wrl/client.h>
#include <d2d1.h>
#include <string>

class D2DRenderer;

class UITextComponent : public UIComponent
{
public:
	virtual ~UITextComponent() = default;
	void SetText(const std::wstring& text);
	void SetFontSize(float size);
	void SetColor(const D2D1_COLOR_F& color);
	void Render(D2DRenderer* renderer);

	std::string GetTypeName() override { return "UITextComponent"; }

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;
private:
	std::wstring m_Text;
	float m_FontSize = 16.0f;
	D2D1_COLOR_F m_Color = D2D1::ColorF(D2D1::ColorF::Black);

	Microsoft::WRL::ComPtr<IDWriteTextFormat> m_TextFormat;
	Microsoft::WRL::ComPtr<IDWriteTextLayout> m_TextLayout;
};

