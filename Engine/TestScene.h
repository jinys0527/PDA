#pragma once
#include "Scene.h"
#include <memory>
#include "BlackBoard.h"
#include "BossBehaviorTree.h"

class BossBehaviorTree;
class BlackBoard;

class TestScene : public Scene
{
public:
	TestScene(EventDispatcher& eventDispatcher, 
		AssetManager& assetManager, 
		SoundAssetManager& soundAssetManager,
		SoundManager& soundManager, 
		D2DRenderer& renderer, 
		UIManager& uiManager) : Scene(eventDispatcher, assetManager, soundAssetManager, soundManager, renderer, uiManager) {}
	virtual ~TestScene() = default;

	void Initialize() override;
	void Finalize()  override;

	void Enter() override;
	void Leave() override;

	void FixedUpdate() override;
	void Update(float deltaTime) override;

	void Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo) override;

private:
	//Çàµ¿Æ®¸® Å×½ºÆ®¿ëµµ
	float m_BTElapsedTime = 0.0f;
	float m_OneSecondTimer = 0.0f;
	std::unique_ptr<BossBehaviorTree> m_BehaviorTree;
	std::unique_ptr<BlackBoard> m_BlackBoard;
	int cnt = 0;
};

