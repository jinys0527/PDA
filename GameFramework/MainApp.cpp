#include "pch.h"
#include "MainApp.h"
#include "SimpleMathHelper.h"
#include "GameObject.h"
#include "CameraObject.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"

bool MainApp::Initialize()
{
	const wchar_t* className = L"GameFramework";
	const wchar_t* windowName = L"GameFramework";

	if (false == Create(className, windowName, 1024, 800))
	{
		return false;
	}
	m_EventDispatcher = std::make_unique<EventDispatcher>();
	m_InputManager = std::make_unique<InputManager>(*m_EventDispatcher);
	m_Renderer = std::make_unique<D2DRenderer>();
	m_AssetManager = std::make_unique<AssetManager>(*m_Renderer);

	m_Renderer->Initialize(m_hwnd);

	m_GameTimer.Reset();

	m_Player = new GameObject(*m_EventDispatcher);
	m_Player->AddComponent<SpriteRenderer>();
	TransformComponent* trans = m_Player->GetComponent<TransformComponent>();
	trans->SetPosition({ 200.0f, 400.0f });
	m_EventDispatcher->AddListener(EventType::KeyDown, trans);
	m_EventDispatcher->AddListener(EventType::KeyUp, trans);
	BoxColliderComponent* bx = m_Player->AddComponent<BoxColliderComponent>();
	bx->Start();

	m_Obstacle = new GameObject(*m_EventDispatcher);
	m_Obstacle->AddComponent<SpriteRenderer>();
	trans = m_Obstacle->GetComponent < TransformComponent>();
	trans->SetPosition({ 700.0f, 300.0f });
	bx = m_Obstacle->AddComponent<BoxColliderComponent>();
	bx->Start();


	m_TestBitmap = m_AssetManager->LoadTexture(L"cat_texture", L"../Resource/cat.png");
	assert(m_TestBitmap != nullptr && "Failed to load test bitmap.");

	m_Background = m_AssetManager->LoadTexture(L"vecteezy", L"../Resource/vecteezy.png");
	assert(m_Background != nullptr && "Failed to load background texture.");


	SpriteRenderer* sr = m_Player->GetComponent<SpriteRenderer>();
	sr->SetTexture(m_TestBitmap);


	sr = m_Obstacle->GetComponent< SpriteRenderer>();
	sr->SetTexture(m_TestBitmap);
	

	return true;
}

void MainApp::Run()
{
	MSG msg = { 0 };

	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (false == m_InputManager->OnHandleMessage(msg))
				TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			UpdateTime();
			Update();
			UpdateInput();
			UpdateLogic();
			Render();
		}
	}
}

void MainApp::Finalize()
{
	if (m_Player)
	{
		delete m_Player;
	}
	if (m_Camera)
		delete m_Camera;
	if (m_Obstacle)
		delete m_Obstacle;
	__super::Destroy();

}

bool MainApp::OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return false;
}

void MainApp::UpdateTime()
{
	m_GameTimer.Tick();
}

void MainApp::UpdateInput()
{
}

void MainApp::UpdateLogic()
{
	m_InputManager->Update();
}

void MainApp::Update()
{
	m_Player->Update(m_GameTimer.DeltaTime());

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
}

void MainApp::Render()
{
	if (m_Renderer == nullptr) return;

	D2D1_SIZE_F srcSize = m_TestBitmap->GetSize();
	D2D1_RECT_F srcRect = D2D1::RectF(0.0f, 0.0f, srcSize.width, srcSize.height);

	m_Renderer->SetTarget();

	m_Renderer->GetD2DContext()->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);

	m_Renderer->RenderBegin();

	m_Renderer->SetTransform(D2D1::Matrix3x2F::Identity());

	//배경 그리기
	if (m_Background != nullptr)
	{
		D2D1_SIZE_F bgSize = m_Background->GetSize();
		D2D1_RECT_F bgRect = D2D1::RectF(0.f, 0.f, bgSize.width * 2, bgSize.height * 2);

		m_Renderer->DrawBitmap(m_Background.Get(), bgRect);
	}

	TransformComponent trans = *m_Player->RenderPosition();
	Math::Vector2F pos = trans.GetPosition();

	m_Renderer->SetTransform(D2D1::Matrix3x2F::Translation(pos.x - srcSize.width/2, pos.y - srcSize.height / 2));

	SpriteRenderer sp = *m_Player->RenderTexture();
	ID2D1Bitmap1* bmp = *sp.GetTexture().GetAddressOf();

	m_Renderer->DrawBitmap(bmp, srcRect);

	m_Renderer->SetTransform(D2D1::Matrix3x2F::Identity());
	BoxColliderComponent* bx = m_Player->GetComponent<BoxColliderComponent>();
	bx->SetSize({ srcSize.width, srcSize.height });
	float left = bx->GetCenter().x - bx->GetSize().x / 2;
	float top = bx->GetCenter().y - bx->GetSize().y / 2;
	float right = bx->GetCenter().x + bx->GetSize().x / 2;
	float bottom = bx->GetCenter().y + bx->GetSize().y / 2;
	m_Renderer->DrawRectangle(left, top, right, bottom, D2D1::ColorF::Black);

	trans = *m_Obstacle->RenderPosition();
	pos = trans.GetPosition();

	m_Renderer->SetTransform(D2D1::Matrix3x2F::Translation(pos.x - srcSize.width / 2, pos.y - srcSize.height / 2));

	sp = *m_Obstacle->RenderTexture();
	bmp = *sp.GetTexture().GetAddressOf();

	m_Renderer->DrawBitmap(bmp, srcRect);

	m_Renderer->SetTransform(D2D1::Matrix3x2F::Identity());
	bx = m_Obstacle->GetComponent<BoxColliderComponent>();
	bx->SetSize({ srcSize.width, srcSize.height });
	left = bx->GetCenter().x - bx->GetSize().x / 2;
	top = bx->GetCenter().y - bx->GetSize().y / 2;
	right = bx->GetCenter().x + bx->GetSize().x / 2;
	bottom = bx->GetCenter().y + bx->GetSize().y / 2;
	m_Renderer->DrawRectangle(left, top, right, bottom, D2D1::ColorF::Black);

	m_Renderer->RenderEnd();
}

void MainApp::OnResize(int width, int height)
{
	__super::OnResize(width, height);
}

void MainApp::OnClose()
{
}
