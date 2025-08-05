#pragma once
#include "Scene.h"
//#include "BlackBoard.h"

class BTNode;
class BlackBoard;

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
	//행동트리 테스트용도
	float m_BTElapsedTime = 0.0f;
	std::shared_ptr<BTNode> m_BehaviorTree;
	BlackBoard* m_BlackBoard;
	int cnt = 0;
};

