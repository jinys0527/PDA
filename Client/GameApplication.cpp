#include "pch.h"
#include "GameApplication.h"
#include "SimpleMathHelper.h"
#include "GameObject.h"
#include "CameraObject.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"

#include "CameraComponent.h"
#include "Background.h"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#include "PlayerObject.h"
#include "RunPlayerController.h"

bool GameApplication::Initialize()
{
	const wchar_t* className  = L"PDA";
	const wchar_t* windowName = L"PDA";

	if (false == Create(className, windowName, 1920, 1080))
	{
		return false;
	}
	
	m_Engine.GetRenderer().Initialize(m_hwnd);

	auto assetManager = m_Engine.GetAssetManager();

	m_TestBitmap = m_Engine.GetAssetManager().LoadTexture(L"cat_texture", L"../Resource/cat.png");
	m_SceneManager.Initialize();
 	m_TestBitmap = m_Engine.GetAssetManager().LoadTexture(L"cat_texture", L"../Resource/cat.png");

 	assert(m_TestBitmap != nullptr && "Failed to load test bitmap.");
 
 	m_Background = m_Engine.GetAssetManager().LoadTexture(L"vecteezy", L"../Resource/vecteezy.png");
 	assert(m_Background != nullptr && "Failed to load background texture.");

	ID3D11RenderTargetView* rtvs[] = { m_Engine.GetRenderer().GetD3DRenderTargetView() };


	return true;
}

void GameApplication::Run()
{
	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (false == m_Engine.GetInputManager().OnHandleMessage(msg))
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
 			m_Engine.UpdateTime();
 			Update();
 			m_Engine.UpdateInput();
 			UpdateLogic();
 			Render();
		}
	}
}

void GameApplication::Finalize()
{
	if (m_Player)
	{
		delete m_Player;
	}

	if (m_Obstacle)
	{
		delete m_Obstacle;
	}

	for (auto background : m_BackgroundObj)
	{
		delete background;
	}

	__super::Destroy();

	/*ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();*/

}

bool GameApplication::OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
	{
		return true; // ImGui가 메시지를 처리했으면 true 반환
	}

	return false;
}





void GameApplication::UpdateLogic()
{
}

void GameApplication::Update()
{
	m_SceneManager.Update(m_Engine.GetTimer().DeltaTime());
	// FixedUpdate
	{

		while (m_fFrameCount >= 0.016f)
		{
			m_fFrameCount -= 0.016f;
		}

	}

}

void GameApplication::Render()
{
	m_Engine.GetRenderer().SetTransform(D2D1::Matrix3x2F::Identity());

	m_Engine.GetRenderer().RenderBegin();

	m_SceneManager.Render();

	m_Engine.GetRenderer().RenderEnd(false);
  
	m_Engine.GetRenderer().Present();
}

void GameApplication::RenderImGUI()
{
	ID3D11DeviceContext* pd3dDeviceContext = nullptr;
	pd3dDeviceContext = m_Engine.GetRenderer().GetD3DContext();
	ID3D11RenderTargetView* rtvs[] = { m_Engine.GetRenderer().GetD3DRenderTargetView() };

	if (pd3dDeviceContext == nullptr || rtvs[0] == nullptr)
	{
		return; // 렌더링 컨텍스트나 뷰가 없으면 리턴
	}
	m_Engine.GetRenderer().GetD3DContext()->OMSetRenderTargets(1, rtvs, nullptr);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	//m_Editor.Update();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}

void GameApplication::OnResize(int width, int height)
{
	__super::OnResize(width, height);
}

void GameApplication::OnClose()
{
}
