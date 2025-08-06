#pragma once
#include "UIComponent.h"
#include "UIImageComponent.h"
#include "Event.h"

class UIImageComponent;

enum class FillDirection
{
	LeftToRight,
	RightToLeft,
	BottomToTop,
	TopToBottom
};

class UISliderComponent : public UIComponent
{
public:
	static constexpr const char* StaticTypeName = "UISliderComponent";
	const char* GetTypeName() const override { return StaticTypeName; }

	UISliderComponent();
	virtual ~UISliderComponent() = default;

	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;

	void SetFrame(UIImageComponent* frameImage)
	{
		m_Frame = frameImage;
	}
	void SetFill(UIImageComponent* fillImage)
	{
		m_Fill = fillImage;
		auto rect = m_Fill->GetUV();
		m_MinX = rect.left;
		m_MaxX = rect.right;
		m_Width = m_MaxX - m_MinX;
	}
	void SetValue(float value)
	{
		std::clamp(value, 0.0f, 1.0f);

		if (m_Value != value)
		{
			m_Value = value;
			m_IsDirty = true;

			if (m_OnValueChanged)
				m_OnValueChanged(m_Value);
		}
	}

	float GetValue() const
	{
		return m_Value;
	}

	void SetOnValueChanged(const std::function<void(float)>& callback)
	{
		m_OnValueChanged = callback;
	}

	void UpdateFillImage();

private:
	UIImageComponent* m_Frame;
	UIImageComponent* m_Fill;
	float m_Value;
	float m_MinX;
	float m_MaxX;
	float m_Width;
	POINT m_CurrentMousePos;
	bool m_IsDragging = false;
	FillDirection m_Direction = FillDirection::LeftToRight;
	bool m_IsDirty = false;
	std::function<void(float)> m_OnValueChanged;
};

