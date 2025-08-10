#pragma once
#include "Scene.h"

class CharacterScene : public Scene
{
public:
	CharacterScene(EventDispatcher& eventDispatcher,
		AssetManager& assetManager,
		SoundAssetManager& soundAssetManager,
		SoundManager& soundManager,
		D2DRenderer& renderer,
		UIManager& uiManager) : Scene(eventDispatcher, assetManager, soundAssetManager, soundManager, renderer, uiManager) {
	}
	virtual ~CharacterScene() = default;

	void Initialize() override;
	void Finalize()  override;

	void Enter() override;
	void Leave() override;

	void FixedUpdate() override;
	void Update(float deltaTime) override;

	void Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo) override;

};

