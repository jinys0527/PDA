#pragma once
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

	void Serialize(nlohmann::json& j) const override{};
	void Deserialize(const nlohmann::json& j) override{};

	void SetCameraObject(GameObject* cameraObject);

private:
	void IsHovered(POINT mousePos);

	GameObject* m_CameraObject;

	bool m_IsHovered = false;
	bool m_IsClicked = false;
	bool m_IsFirst = false;
};

