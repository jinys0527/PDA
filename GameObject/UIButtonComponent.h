#pragma once
#include "UIComponent.h"
#include <d2d1.h>
#include "functional"

class D2DRenderer;

class UIButtonComponent : public UIComponent
{
public:
	virtual ~UIButtonComponent() = default;
	void SetOnClick(std::function<void()> callback);
	void Render(D2DRenderer* renderer);
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
	std::string GetTypeName() override { return "UIButtonComponent"; }

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;

private:
	std::function<void()> m_OnClick;

	D2D1_COLOR_F m_DefaultColor = D2D1::ColorF(D2D1::ColorF::LightGray);
	D2D1_COLOR_F m_HoveredColor = D2D1::ColorF(D2D1::ColorF::Gray);
	D2D1_COLOR_F m_PressedColor = D2D1::ColorF(D2D1::ColorF::DarkGray);
};

