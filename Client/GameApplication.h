#pragma once

#include "NzWndBase.h"
#include <wrl/client.h>
#include "Engine.h"
#include "SceneManager.h"
#include "Editor.h"

class GameObject;
class CameraObject;

class GameApplication : public NzWndBase
{
public:
	GameApplication(Engine& engine, SceneManager& sceneManager) : NzWndBase(), m_Engine(engine), m_SceneManager(sceneManager) { }
	virtual ~GameApplication() = default;

	bool Initialize();
	void Run();
	void Finalize();

	bool OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) override;

private:
	void UpdateInput();
	void UpdateLogic();
	void Update();

	void Render();
	void RenderImGUI();
	
	void OnResize(int width, int height) override;
	void OnClose() override;

	Microsoft::WRL::ComPtr<ID2D1Bitmap1>        m_TestBitmap;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1>        m_Background;

	GameObject* m_Player;
	GameObject* m_Obstacle;

	std::array<GameObject*, 2> m_BackgroundObj;

	// fixedupdate용 시간
	float m_fFrameCount;

	//Editor& m_Editor;

	Engine& m_Engine;
	SceneManager& m_SceneManager;
};

