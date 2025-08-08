#pragma once
#include "GameObject.h"
#include "GraffitiComponent.h"

class AssetManager;

class GraffitiObject : public GameObject
{
public:
	GraffitiObject(EventDispatcher& eventDispatcher);
	virtual ~GraffitiObject() = default;

	void Render(std::vector<RenderInfo>& renderInfo) override;

	void SetGravitti(AssetManager* assetManager);

private:
	GraffitiComponent* m_GraffitiComponent;
	int m_RandTexture;
	std::list<Microsoft::WRL::ComPtr<ID2D1Bitmap1>> m_GraffitiTextures;
};

