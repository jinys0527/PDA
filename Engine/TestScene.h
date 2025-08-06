#pragma once
#include "Scene.h"
#include <memory>
#include "BlackBoard.h"
#include "BossBehaviorTree.h"

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
	void Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo) override;

private:
	//행동트리 테스트용도
	float m_BTElapsedTime = 0.0f;
	float m_OneSecondTimer = 0.0f;
	std::unique_ptr<BossBehaviorTree> m_BehaviorTree;
	std::unique_ptr<BlackBoard> m_BlackBoard;
	int cnt = 0;
};

