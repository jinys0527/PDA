#pragma once

#include "Component.h"
#include <functional>

#include "RectTransformComponent.h"

class Scene;

class SwitchingAreaComponent : public Component
{
public:
	SwitchingAreaComponent() = default;
	~SwitchingAreaComponent() = default;

	static constexpr const char* StaticTypeName = "SwitchingAreaComponent";
	const char* GetTypeName() const override { return StaticTypeName; }

	void Start(int index);

	void SetFunc(std::function<void()> func) { m_SceneLoadFunc = func; }

	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;

private:
	float m_Opacity = 1;
	bool m_IsLoaded = false;
	bool m_IsStart = false;
	int m_Index = 0;

	Scene* scenePtr;

	std::function<void()> m_SceneLoadFunc;
	RectTransformComponent* m_RectTransComp;

};
