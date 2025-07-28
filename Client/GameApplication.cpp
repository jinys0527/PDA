#include "pch.h"
#include "GameApplication.h"
#include "SimpleMathHelper.h"
#include "GameObject.h"
#include "CameraObject.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"

#include "PlayerObject.h"
#include "RunPlayerController.h"

bool GameApplication::Initialize()
{
	const wchar_t* className  = L"PDA";
	const wchar_t* windowName = L"PDA";

	if (false == Create(className, windowName, 1024, 800))
	{
		return false;
	}
	

	m_Engine.GetRenderer().Initialize(m_hwnd);

	m_Player = new PlayerObject(m_Engine.GetEventDispatcher());
 	m_Player->AddComponent<SpriteRenderer>();
 	TransformComponent* trans = m_Player->GetComponent<TransformComponent>();
 	trans->SetPosition({ 200.0f, 400.0f });
	//RunPlayerController* controller = m_Player->GetComponent<RunPlayerController>();
	//m_Engine.GetEventDispatcher().AddListener(EventType::KeyDown, trans);
	//m_Engine.GetEventDispatcher().AddListener(EventType::KeyUp, trans);
	//m_Engine.GetEventDispatcher().AddListener(EventType::KeyDown, controller);
	//m_Engine.GetEventDispatcher().AddListener(EventType::KeyUp, controller);
 	BoxColliderComponent* bx = m_Player->AddComponent<BoxColliderComponent>();
 	bx->Start();
 
 	m_Obstacle = new GameObject(m_Engine.GetEventDispatcher());
 	m_Obstacle->AddComponent<SpriteRenderer>();
 	trans = m_Obstacle->GetComponent < TransformComponent>();
 	trans->SetPosition({ 700.0f, 300.0f });
 	bx = m_Obstacle->AddComponent<BoxColliderComponent>();
 	bx->Start();
 
 
 	m_TestBitmap = m_Engine.GetAssetManager().LoadTexture(L"cat_texture", L"../Resource/cat.png");
 	assert(m_TestBitmap != nullptr && "Failed to load test bitmap.");
 
 	m_Background = m_Engine.GetAssetManager().LoadTexture(L"vecteezy", L"../Resource/vecteezy.png");
 	assert(m_Background != nullptr && "Failed to load background texture.");
 
 
 	SpriteRenderer* sr = m_Player->GetComponent<SpriteRenderer>();
 	sr->SetTexture(m_TestBitmap);
 
 
 	sr = m_Obstacle->GetComponent< SpriteRenderer>();
 	sr->SetTexture(m_TestBitmap);
	

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
	if (m_Camera)
		delete m_Camera;
	if (m_Obstacle)
		delete m_Obstacle;
	__super::Destroy();

}

bool GameApplication::OnWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return false;
}





void GameApplication::UpdateLogic()
{
}

void GameApplication::Update()
{
	m_Player->Update(m_Engine.GetTimer().DeltaTime());

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

	m_Engine.GetRenderer().SetTransform(D2D1::Matrix3x2F(1, 0, 0, 1, 10, 10));
}

void GameApplication::Render()
{
 	D2D1_SIZE_F srcSize = m_TestBitmap->GetSize();
 	D2D1_RECT_F srcRect = D2D1::RectF(0.0f, 0.0f, srcSize.width, srcSize.height);
 
 	m_Engine.GetRenderer().SetTarget();
 
	m_Engine.GetRenderer().GetD2DContext()->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
 
	m_Engine.GetRenderer().RenderBegin();
 
	//m_Engine.GetRenderer().SetTransform(D2D1::Matrix3x2F::Identity());
 
 	//배경 그리기
 	if (m_Background != nullptr)
 	{
 		D2D1_SIZE_F bgSize = m_Background->GetSize();
 		D2D1_RECT_F bgRect = D2D1::RectF(0.f, 0.f, bgSize.width * 2, bgSize.height * 2);
 
		m_Engine.GetRenderer().DrawBitmap(m_Background.Get(), bgRect);
 	}
 
 	TransformComponent trans = *m_Player->RenderPosition();
 	Math::Vector2F pos = trans.GetPosition();
 
	m_Engine.GetRenderer().SetTransform(D2D1::Matrix3x2F::Translation(pos.x - srcSize.width/2, pos.y - srcSize.height / 2));
 
 	SpriteRenderer sp = *m_Player->RenderTexture();
 	ID2D1Bitmap1* bmp = *sp.GetTexture().GetAddressOf();
 
	m_Engine.GetRenderer().DrawBitmap(bmp, srcRect);
 
	m_Engine.GetRenderer().SetTransform(D2D1::Matrix3x2F::Identity());
 	BoxColliderComponent* bx = m_Player->GetComponent<BoxColliderComponent>();
 	bx->SetSize({ srcSize.width, srcSize.height });
 	float left = bx->GetCenter().x - bx->GetSize().x / 2;
 	float top = bx->GetCenter().y - bx->GetSize().y / 2;
 	float right = bx->GetCenter().x + bx->GetSize().x / 2;
 	float bottom = bx->GetCenter().y + bx->GetSize().y / 2;
	m_Engine.GetRenderer().DrawRectangle(left, top, right, bottom, D2D1::ColorF::Black);
 
 	trans = *m_Obstacle->RenderPosition();
 	pos = trans.GetPosition();
 
	m_Engine.GetRenderer().SetTransform(D2D1::Matrix3x2F::Translation(pos.x - srcSize.width / 2, pos.y - srcSize.height / 2));
 
 	sp = *m_Obstacle->RenderTexture();
 	bmp = *sp.GetTexture().GetAddressOf();
 
	m_Engine.GetRenderer().DrawBitmap(bmp, srcRect);
 
	m_Engine.GetRenderer().SetTransform(D2D1::Matrix3x2F::Identity());
 	bx = m_Obstacle->GetComponent<BoxColliderComponent>();
 	bx->SetSize({ srcSize.width, srcSize.height });
 	left = bx->GetCenter().x - bx->GetSize().x / 2;
 	top = bx->GetCenter().y - bx->GetSize().y / 2;
 	right = bx->GetCenter().x + bx->GetSize().x / 2;
 	bottom = bx->GetCenter().y + bx->GetSize().y / 2;
	m_Engine.GetRenderer().DrawRectangle(left, top, right, bottom, D2D1::ColorF::Black);
 
	m_Engine.GetRenderer().RenderEnd();
}

void GameApplication::OnResize(int width, int height)
{
	__super::OnResize(width, height);
}

void GameApplication::OnClose()
{
}
