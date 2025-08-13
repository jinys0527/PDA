#pragma once
#include "SimpleMathHelper.h"

#include "Windows.h"
#include "Component.h"
#include "IEventListener.h"

class GameObject;

class GraffitiComponent : public Component, public IEventListener
{
public :
	static constexpr const char* StaticTypeName = "GraffitiComponent";
	const char* GetTypeName() const override { return StaticTypeName; }

	GraffitiComponent();
	virtual ~GraffitiComponent();
	void Start();

	void Update(float deltatime) override;

	void OnEvent(EventType type, const void* data) override;
	bool GetIsClicked()
	{
		return m_IsClicked;
	}

	bool GetIsFirst()
	{
		return m_IsFirst;
	}

	void Reset() { m_IsFirst = false; }

	void Serialize(nlohmann::json& j) const override{};
	void Deserialize(const nlohmann::json& j) override{};

private:
	void IsHovered(Math::Vector2F mousePos);

	bool m_IsHovered = false;
	bool m_IsClicked = false;
	bool m_IsFirst = false;
};

