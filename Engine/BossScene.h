#pragma once
#include "Scene.h"
#include <memory>
#include "BlackBoard.h"
#include "BossBehaviorTree.h"
#include "BossEventComponent.h"

class ChapterBackgroundManager;
class GraffitiObject;

class BossScene : public Scene
{
public:
	BossScene(EventDispatcher& eventDispatcher,
		AssetManager& assetManager,
		SoundAssetManager& soundAssetManager,
		SoundManager& soundManager,
		D2DRenderer& renderer,
		UIManager& uiManager) : Scene(eventDispatcher, assetManager, soundAssetManager, soundManager, renderer, uiManager) {
	}
	virtual ~BossScene() = default;

	void Initialize() override;
	void Finalize()  override;

	void Enter() override;
	void Leave() override;

	void FixedUpdate() override;
	void Update(float deltaTime) override;

	void Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo) override;

	void SavePlayerInfo();
	void LoadPlayerInfo();

private:
	void OnLoadComplete();

	float time = 0.f;

	float m_BTElapsedTime = 0.0f;
	float m_OneSecondTimer = 0.0f;
	std::unique_ptr<BossBehaviorTree> m_BehaviorTree;
	std::unique_ptr<BlackBoard> m_BlackBoard;
	int cnt = 0;

	std::vector<std::shared_ptr<Telegraph>> m_Telegraphs;
	std::vector<std::shared_ptr<GameObject>> m_Fires;
	std::vector<std::shared_ptr<GameObject>> m_Bombs;
	std::vector<std::shared_ptr<GameObject>> m_Anims;
	std::vector<std::shared_ptr<GraffitiObject>> m_AttackArea;

	std::unordered_map<std::string, std::shared_ptr<GameObject>> m_Backgrounds;
	std::unique_ptr<BossEventComponent> m_BossEventComponent;
	std::shared_ptr<ChapterBackgroundManager> m_ChapterBackgroundManager;

	std::shared_ptr<GameObject> m_Phase_2_Arm;

	float m_TotalXMove = 0.0f;
	float m_ScrollSpeed = 0.f;


	bool m_IsLoaded = false;
};

