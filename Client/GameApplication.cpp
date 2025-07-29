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

	m_Player = new GameObject(m_Engine.GetEventDispatcher());
 	auto sr = m_Player->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&assetManager);

 	TransformComponent* trans = m_Player->GetComponent<TransformComponent>();
 	trans->SetPosition({ 200.0f, 300.0f });
	m_Engine.GetEventDispatcher().AddListener(EventType::KeyDown, trans);
	m_Engine.GetEventDispatcher().AddListener(EventType::KeyUp, trans);
 	BoxColliderComponent* bx = m_Player->AddComponent<BoxColliderComponent>();
 	bx->Start();
 
	// 카메라 
	m_Camera = new CameraObject(m_Engine.GetEventDispatcher(), 1024, 800);
	trans = m_Camera->GetComponent<TransformComponent>();
	m_Engine.GetEventDispatcher().AddListener(EventType::KeyDown, trans);
	m_Engine.GetEventDispatcher().AddListener(EventType::KeyUp, trans);
	// end 카메라

 	m_Obstacle = new GameObject(m_Engine.GetEventDispatcher());
 	sr = m_Obstacle->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&assetManager);
 	trans = m_Obstacle->GetComponent<TransformComponent>();
 	trans->SetPosition({ 700.0f, 300.0f });
 	bx = m_Obstacle->AddComponent<BoxColliderComponent>();
 	bx->Start();
 

	m_TestBitmap = m_Engine.GetAssetManager().LoadTexture(L"cat_texture", L"../Resource/cat.png");
	m_SceneManager.Initialize();
	m_Camera = m_SceneManager.GetCamera();
	m_Engine.GetRenderer().SetCamera(m_Camera);
 	m_TestBitmap = m_Engine.GetAssetManager().LoadTexture(L"cat_texture", L"../Resource/cat.png");

 	assert(m_TestBitmap != nullptr && "Failed to load test bitmap.");
 
 	m_Background = m_Engine.GetAssetManager().LoadTexture(L"vecteezy", L"../Resource/vecteezy.png");
 	assert(m_Background != nullptr && "Failed to load background texture.");
 
 
 	sr = m_Player->GetComponent<SpriteRenderer>();
 	sr->SetTexture(m_TestBitmap);
 
 
 	sr = m_Obstacle->GetComponent<SpriteRenderer>();
 	sr->SetTexture(m_TestBitmap);
	

	//백그라운드 두개
	for (auto& obj : m_BackgroundObj)
	{
		obj = new Background(m_Engine.GetEventDispatcher());
		obj->AddComponent<SpriteRenderer>();
		sr = obj->GetComponent<SpriteRenderer>();
		sr->SetTexture(m_Background);
	}
	m_BackgroundObj[0]->GetComponent<TransformComponent>()->SetPosition({ 0, 1080 });

	m_BackgroundObj[1]->GetComponent<TransformComponent>()->SetPosition({ 1920, 1080 });

	ImGui::CreateContext();
	ImGui_ImplWin32_Init(m_hwnd);

	ImGui_ImplDX11_Init(m_Engine.GetRenderer().GetD3DDevice(), m_Engine.GetRenderer().GetD3DContext());

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
			//if (false == m_Engine.GetInputManager().OnHandleMessage(msg))
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
	__super::Destroy();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

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

	// FixedUpdate
	{
		m_fFrameCount += m_Engine.GetTimer().DeltaTime();
		
		std::cout << m_fFrameCount << std::endl;

		while (m_fFrameCount >= 0.016f)
		{
			for (auto& obj : m_BackgroundObj)
			{
				obj->FixedUpdate();
			}
			m_fFrameCount -= 0.016f;
		}

	}

	m_Player->Update(m_Engine.GetTimer().DeltaTime());

	Math::Vector2F pos = m_Camera->GetComponent<TransformComponent>()->GetPosition();

	//m_Camera->GetComponent<TransformComponent>()->SetPosition({pos.x + 50.f * m_Engine.GetTimer().DeltaTime(), pos.y});

	auto* playerCol = m_Player->GetComponent<BoxColliderComponent>();
	auto* obsCol = m_Obstacle->GetComponent<BoxColliderComponent>();

	bool isColliding = playerCol->BoxVsBox(*obsCol);
	CollisionState prevState = playerCol->GetCollisionState();

	if (isColliding)
	{
		if (prevState == CollisionState::None || prevState == CollisionState::Exit)
		{
			playerCol->SetCollisionState(CollisionState::Enter);
			printf("Collision Enter\n");
		}
		else
		{
			playerCol->SetCollisionState(CollisionState::Stay);
			printf("Collision Stay\n");
		}
	}
	else
	{
		if (prevState == CollisionState::Enter || prevState == CollisionState::Stay)
		{
			playerCol->SetCollisionState(CollisionState::Exit);
			printf("Collision Exit\n");
		}
		else
		{
			playerCol->SetCollisionState(CollisionState::None);
		}
	}

	//백그라운드 업데이트
	for (auto& obj : m_BackgroundObj)
	{
		obj->Update(m_Engine.GetTimer().DeltaTime());
	}

// 	m_Player->Update(m_Engine.GetTimer().DeltaTime());
// 
// 	auto* playerCol = m_Player->GetComponent<BoxColliderComponent>();
// 	auto* obsCol = m_Obstacle->GetComponent<BoxColliderComponent>();
// 
// 	bool isColliding = playerCol->BoxVsBox(*obsCol);
// 	CollisionState prevState = playerCol->GetCollisionState();
// 
// 	if (isColliding)
// 	{
// 		if (prevState == CollisionState::None || prevState == CollisionState::Exit)
// 		{
// 			playerCol->SetCollisionState(CollisionState::Enter);
// 			printf("Collision Enter\n");
// 		}
// 		else
// 		{
// 			playerCol->SetCollisionState(CollisionState::Stay);
// 			printf("Collision Stay\n");
// 		}
// 	}
// 	else
// 	{
// 		if (prevState == CollisionState::Enter || prevState == CollisionState::Stay)
// 		{
// 			playerCol->SetCollisionState(CollisionState::Exit);
// 			printf("Collision Exit\n");
// 		}
// 		else
// 		{
// 			playerCol->SetCollisionState(CollisionState::None);
// 		}
// 	}
}

void GameApplication::Render()
{
	D2D1_SIZE_F srcSize = m_TestBitmap->GetSize();
	D2D1_RECT_F srcRect = D2D1::RectF(0.0f, 0.0f, srcSize.width, srcSize.height);

	m_Engine.GetRenderer().SetTarget();
	m_Engine.GetRenderer().GetD2DContext()->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
	m_Engine.GetRenderer().RenderBegin();


	//------------------------------------
	// 렌더용 행렬 계산
	D2D1::Matrix3x2F cameraTM = m_Camera->GetComponent<CameraComponent>()->GetViewMatrix();
	D2D1::Matrix3x2F renderTM = D2D1::Matrix3x2F::Scale(1, -1) * D2D1::Matrix3x2F::Translation(0, 1080);
	D2D1::Matrix3x2F finalTM = renderTM * cameraTM;

	m_Engine.GetRenderer().SetTransform(finalTM);
	//------------------------------------


	//------------------------------------
	// 배경 먼저 렌더
	SpriteRenderer sp;
	TransformComponent trans;
	ID2D1Bitmap1* bmp;
	Math::Vector2F pos;
	srcRect = D2D1::RectF(0.0f, 0.0f, 1920, 1080);

	for (auto& obj : m_BackgroundObj)
	{
		sp = *obj->RenderTexture();
		bmp = *sp.GetTexture().GetAddressOf();
		trans = *obj->RenderPosition();
		pos = trans.GetPosition();
		m_Engine.GetRenderer().DrawBitmap(bmp, srcRect, &trans, finalTM);
	}

	//------------------------------------

	// 플레이어
	//std::cout << m_Player->GetComponent<TransformComponent>()->GetWorldMatrix().dx
	//	<< " " << m_Player->GetComponent<TransformComponent>()->GetWorldMatrix().dy
	//	<< std::endl;

	trans = *m_Player->RenderPosition();
	pos = trans.GetPosition();

	sp = *m_Player->RenderTexture();
	bmp = *sp.GetTexture().GetAddressOf();

	srcRect = D2D1::RectF(0.0f, 0.0f, srcSize.width, srcSize.height);
	m_Engine.GetRenderer().DrawBitmap(bmp, srcRect, &trans, finalTM);

	BoxColliderComponent* bx = m_Player->GetComponent<BoxColliderComponent>();
	bx->SetSize({ srcSize.width, srcSize.height });

	// 장애물
	trans = *m_Obstacle->RenderPosition();
	pos = trans.GetPosition();

	m_Engine.GetRenderer().DrawBitmap(bmp, srcRect, &trans, finalTM);
	bx = m_Obstacle->GetComponent<BoxColliderComponent>();
	bx->SetSize({ srcSize.width, srcSize.height });

	m_Engine.GetRenderer().RenderEnd();
 
	m_Engine.GetRenderer().SetTransform(D2D1::Matrix3x2F::Identity());
 
	m_SceneManager.Render();
 	//배경 그리기
//   	if (m_Background != nullptr)
//   	{
//   		D2D1_SIZE_F bgSize = m_Background->GetSize();
//   		D2D1_RECT_F bgRect = D2D1::RectF(0.f, 0.f, bgSize.width * 2, bgSize.height * 2);
//   
//  		m_Engine.GetRenderer().DrawBitmap(m_Background.Get(), bgRect);
//   	}
//   
//   	TransformComponent trans = *m_Player->RenderPosition();
//   	Math::Vector2F pos = trans.GetPosition();
//   
//  	m_Engine.GetRenderer().SetTransform(D2D1::Matrix3x2F::Translation(pos.x - srcSize.width/2, pos.y - srcSize.height / 2));
//   
//   	SpriteRenderer sp = *m_Player->RenderTexture();
//   	ID2D1Bitmap1* bmp = *sp.GetTexture().GetAddressOf();
//   
//  	m_Engine.GetRenderer().DrawBitmap(bmp, srcRect);
//   
//  	m_Engine.GetRenderer().SetTransform(D2D1::Matrix3x2F::Identity());
//   	BoxColliderComponent* bx = m_Player->GetComponent<BoxColliderComponent>();
//   	bx->SetSize({ srcSize.width, srcSize.height });
//   	float left = bx->GetCenter().x - bx->GetSize().x / 2;
//   	float top = bx->GetCenter().y - bx->GetSize().y / 2;
//   	float right = bx->GetCenter().x + bx->GetSize().x / 2;
//   	float bottom = bx->GetCenter().y + bx->GetSize().y / 2;
//  	m_Engine.GetRenderer().DrawRectangle(left, top, right, bottom, D2D1::ColorF::Black);
//   
//   	trans = *m_Obstacle->RenderPosition();
//   	pos = trans.GetPosition();
//   
//  	m_Engine.GetRenderer().SetTransform(D2D1::Matrix3x2F::Translation(pos.x - srcSize.width / 2, pos.y - srcSize.height / 2));
//   
//   	sp = *m_Obstacle->RenderTexture();
//   	bmp = *sp.GetTexture().GetAddressOf();
//   
//  	m_Engine.GetRenderer().DrawBitmap(bmp, srcRect);
//   
//  	m_Engine.GetRenderer().SetTransform(D2D1::Matrix3x2F::Identity());
//   	bx = m_Obstacle->GetComponent<BoxColliderComponent>();
//   	bx->SetSize({ srcSize.width, srcSize.height });
//   	left = bx->GetCenter().x - bx->GetSize().x / 2;
//   	top = bx->GetCenter().y - bx->GetSize().y / 2;
//   	right = bx->GetCenter().x + bx->GetSize().x / 2;
//   	bottom = bx->GetCenter().y + bx->GetSize().y / 2;
//  	m_Engine.GetRenderer().DrawRectangle(left, top, right, bottom, D2D1::ColorF::Black);

	m_Engine.GetRenderer().RenderEnd(false);

	RenderImGUI();

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

	m_Editor.Update();

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
