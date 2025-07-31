#pragma once
#include "Component.h"
#include <vector>
#include "IEventListener.h"

class RectTransformComponent;

class UIComponent : public Component, public IEventListener
{
public:
	
	static constexpr const char* StaticTypeName = "UIComponent";
	const char* GetTypeName() const override { return StaticTypeName; }

	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;
protected:
	RectTransformComponent* m_RectTransform = nullptr;

	enum class UIInteractionState {None, Hovered, Pressed, Released};
	UIInteractionState m_State = UIInteractionState::None;

	bool m_Visible = true;
	int m_ZOrder = 0;
	float m_Opacity = 1.0f;
};

REGISTER_COMPONENT(UIComponent);