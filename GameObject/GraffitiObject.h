#pragma once
#include "GameObject.h"
#include "GraffitiComponent.h"

class AssetManager;
class SpriteRenderer;

class GraffitiObject : public GameObject
{
public:
	GraffitiObject(EventDispatcher& eventDispatcher);
	virtual ~GraffitiObject() = default;

	void Render(std::vector<RenderInfo>& renderInfo) override;

	void SetGravittis(AssetManager* assetManager, int chapter);

	void Start(AssetManager* assetManager, int chapter);

private:
	GraffitiComponent* m_GraffitiComponent;
	SpriteRenderer* m_Sprite;
	int m_RandTexture;
	std::vector<Microsoft::WRL::ComPtr<ID2D1Bitmap1>> m_GraffitiTextures;
};

