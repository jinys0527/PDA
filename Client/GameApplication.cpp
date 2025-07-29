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

bool GameApplication::Initialize()
{
	const wchar_t* className  = L"PDA";
	const wchar_t* windowName = L"PDA";

	if (false == Create(className, windowName, 1920, 1080))
	{
		return false;
	}
	

	m_Engine.GetRenderer().Initialize(m_hwnd);

	m_Player = new GameObject(m_Engine.GetEventDispatcher());
 	m_Player->AddComponent<SpriteRenderer>();
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

	// FixedUpdate
	{
		m_fFrameCount += m_Engine.GetTimer().DeltaTime();
		while (m_fFrameCount >= 16.0f)
		{

			m_fFrameCount -= 16.0f;
		}

	}

	std::cout << m_Engine.GetTimer().TotalTime() << std::endl;

	m_Player->Update(m_Engine.GetTimer().DeltaTime());

	Math::Vector2F pos = m_Camera->GetComponent<TransformComponent>()->GetPosition();

	m_Camera->GetComponent<TransformComponent>()->SetPosition({pos.x + 50.f * m_Engine.GetTimer().DeltaTime(), pos.y});

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
	//	<< m_Player->GetComponent<TransformComponent>()->GetWorldMatrix().dy
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
}

void GameApplication::OnResize(int width, int height)
{
	__super::OnResize(width, height);
}

void GameApplication::OnClose()
{
}
