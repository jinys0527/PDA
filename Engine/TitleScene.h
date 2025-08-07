#pragma once
#include "Scene.h"
#include <memory>
#include "BlackBoard.h"
#include "BossBehaviorTree.h"

class TitleScene : public Scene
{
public:
	TitleScene(EventDispatcher& eventDispatcher, AssetManager& assetManager, SoundAssetManager& soundAssetManager, SoundManager& soundManager) : Scene(eventDispatcher, assetManager, soundAssetManager, soundManager) {}
	virtual ~TitleScene() = default;

	void Initialize() override;
	void Finalize() override;

	void Enter() override;
	void Leave() override;

	void FixedUpdate() override;
	void Update(float deltaTime) override;
	void Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo) override;
	
private:
};

