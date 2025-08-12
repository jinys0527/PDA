#pragma once

#include "Component.h"
#include <vector>
#include "IEventListener.h"

class TransformComponent;
class AnimationComponent;

class PlayerEffectComponent : public Component, public IEventListener
{
public:
	static constexpr const char* StaticTypeName = "PlayerEffectComponent";
	const char* GetTypeName() const override { return StaticTypeName; }

	~PlayerEffectComponent();

	void Start();

	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;
protected:
	TransformComponent* m_TransformComponent;
	AnimationComponent* m_AnimationComponent;
};

