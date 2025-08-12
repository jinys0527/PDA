#pragma once
#include "Scene.h"
#include <memory>
#include <unordered_map>

class GameObject;

class GameScene : public Scene
{
public:
	GameScene(EventDispatcher& eventDispatcher,
		AssetManager& assetManager,
		SoundAssetManager& soundAssetManager,
		SoundManager& soundManager,
		D2DRenderer& renderer,
		UIManager& uiManager)
		: Scene(eventDispatcher, assetManager, soundAssetManager, soundManager, renderer, uiManager) {
	}
	virtual ~GameScene() = default;

	void Initialize() override;
	void Finalize() override;

	void Enter() override;
	void Leave() override;

	void FixedUpdate() override;
	void Update(float deltaTime) override;
	void Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo) override;
	
};

