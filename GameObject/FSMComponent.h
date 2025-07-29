#pragma once
#include "Component.h"
#include "FSM.h"
#include <string>

class FSMComponent : public Component
{
public:	
	static constexpr const char* StaticTypeName = "FSMComponent";
	const char* GetTypeName() const override { return StaticTypeName; }
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;
private:
	FSM m_Fsm;
};

REGISTER_COMPONENT(FSMComponent);