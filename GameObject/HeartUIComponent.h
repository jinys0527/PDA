#pragma once
#include "Component.h"


class HeartUIComponent : public Component, public IEventListener
{
public:
	HeartUIComponent() = default;
	virtual ~HeartUIComponent();
	static constexpr const char* StaticTypeName = "HeartUIComponent";
	const char* GetTypeName() const override { return StaticTypeName; }

	void Start();

	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;

	void SetHpLoc(int value) { m_HpLoc = value; }

protected:
	float m_HpLoc = 0;
};

