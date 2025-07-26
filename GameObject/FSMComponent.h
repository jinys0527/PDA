#pragma once
#include "Component.h"
#include "FSM.h"
#include <string>

class FSMComponent : public Component
{
public:
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
	std::string GetTypeName() override { return "FSMComponent"; }

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;
private:
	FSM m_Fsm;
};

