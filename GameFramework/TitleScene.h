#pragma once
#include "Scene.h"

class TitleScene : public Scene
{
public:
	virtual ~TitleScene() = default;

	void Initialize(NzWndBase* pWnd) override;
	void Finalize() override;

	void Enter() override;
	void Leave() override;

	void FixedUpdate() override {}
	void Update(float deltaTime) override;
	void Render(HDC hDC) override;
	
private:
};

