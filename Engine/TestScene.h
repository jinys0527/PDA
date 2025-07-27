#pragma once
#include "Scene.h"

class TestScene : public Scene
{
	TestScene() = default;
	virtual ~TestScene() = default;

	void Initialize() override;
	void Finalize()  override;

	void Enter() override;
	void Leave() override;

	void FixedUpdate() override;
	void Update(float deltaTime) override;
	void Render(std::vector<RenderInfo>& renderInfo) override;
};

