#pragma once

#include "NzWndBase.h"
#include "GameTimer.h"
#include <memory>

#include <wrl/client.h>
#include "EventDispatcher.h"
#include "InputManager.h"
#include "D2DRenderer.h"
#include "AssetManager.h"

class GameObject;
class CameraObject;

class MainApp : public NzWndBase
{
public:
	MainApp() : NzWndBase(){ }
	virtual ~MainApp() = default;

	bool Initialize();
	void Run();
	void Finalize();

	bool OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) override;

private:
	void UpdateTime();
	void UpdateInput();
	void UpdateLogic();
	void Update();

	void Render();
	
	void OnResize(int width, int height) override;
	void OnClose() override;

	GameTimer m_GameTimer;

	ComPtr<ID2D1Bitmap1>        m_TestBitmap;

	ComPtr<ID2D1Bitmap1>        m_Background;

	GameObject* m_Player;
	CameraObject* m_Camera;
	GameObject* m_Obstacle;

	std::unique_ptr<EventDispatcher> m_EventDispatcher = nullptr;
	std::unique_ptr<InputManager> m_InputManager = nullptr;
	std::unique_ptr<D2DRenderer> m_Renderer = nullptr;
	std::unique_ptr<AssetManager> m_AssetManager = nullptr;
};

