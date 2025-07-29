#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	TitleScene(EventDispatcher& eventDispatcher, AssetManager& assetManager) : Scene(eventDispatcher, assetManager) {}
	virtual ~TitleScene() = default;

	void Initialize() override;
	void Finalize() override;

	void Enter() override;
	void Leave() override;

	void FixedUpdate() override {}
	void Update(float deltaTime) override;
	void Render(std::vector<RenderInfo>& renderInfo) override;
	
private:
};

