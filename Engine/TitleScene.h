#pragma once
#include "Scene.h"
#include <memory>
#include "BlackBoard.h"
#include "BossBehaviorTree.h"

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
	//�ൿƮ�� �׽�Ʈ�뵵
	float m_BTElapsedTime = 0.0f;
	float m_OneSecondTimer = 0.0f;
	std::unique_ptr<BossBehaviorTree> m_BehaviorTree;
	std::unique_ptr<BlackBoard> m_BlackBoard;
	int cnt = 0;
};

