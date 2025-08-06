#pragma once
#include "Scene.h"

class TestScene : public Scene
{
public:
	TestScene(EventDispatcher& eventDispatcher, AssetManager& assetManager, SoundAssetManager& soundAssetManager,SoundManager& soundManager) : Scene(eventDispatcher, assetManager, soundAssetManager, soundManager) {}
	virtual ~TestScene() = default;

	void Initialize() override;
	void Finalize()  override;

	void Enter() override;
	void Leave() override;

	void FixedUpdate() override;
	void Update(float deltaTime) override;
	void Render(std::vector<RenderInfo>& renderInfo) override;
};

