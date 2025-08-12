#pragma once
#include "UIComponent.h"
#include "GameObject.h"
#include "GraffitiComponent.h"

class AssetManager;

class BulletUIComponent : public UIComponent
{
public:
	BulletUIComponent() = default;
	virtual ~BulletUIComponent();
	static constexpr const char* StaticTypeName = "BulletUIComponent";
	const char* GetTypeName() const override { return StaticTypeName; }

	void Start();

	void SetNumbers(AssetManager* assetManager);

	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;

	void Serialize(nlohmann::json& j) const override;
	void Deserialize(const nlohmann::json& j) override;

	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>> m_NumberBitmaps;
};

