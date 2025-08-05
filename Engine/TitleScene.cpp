#include "pch.h"
#include "TitleScene.h"
#include "InputManager.h"
#include "TestListener.h"
#include "GameObject.h"
#include "CameraObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "PlayerObject.h"
#include "ButtonUI.h"
#include "CameraComponent.h"
#include "UIImageComponent.h"
#include "GraffitiObject.h"
#include "GraffitiComponent.h"
#include "BoxColliderComponent.h"
#include "Obstacle.h"
#include "AnimationComponent.h"

void TitleScene::Initialize()
{
	auto gameObject = std::make_shared<PlayerObject>(m_EventDispatcher);
	gameObject->m_Name = "test";
	//m_EventDispatcher.AddListener()
	auto trans = gameObject->GetComponent<TransformComponent>();
	trans->SetPosition({ 960.0f, 540.0f });
	auto sr = gameObject->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
	sr->SetPath("../Resource/cat.png");
	sr->SetTextureKey("cat_texture");
	sr->SetTexture(bitmap);
	sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());


	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans3 = cameraObject->GetComponent<TransformComponent>();
	trans3->SetPosition({ 960.0f, 540.0f });
	cameraObject->GetComponent<CameraComponent>()->SetZoom(0.5);
	SetMainCamera(cameraObject);


	auto testUIObject = std::make_shared<ButtonUI>(m_EventDispatcher);
	testUIObject->m_Name = "UI";
	auto uiTrans = testUIObject->GetComponent<TransformComponent>();
	uiTrans->SetPosition({ 960, 540 });
	//sr = testUIObject->AddComponent<SpriteRenderer>();
	auto image = testUIObject->AddComponent<UIImageComponent>();
	image->SetBitmap(bitmap);
	//sr->SetAssetManager(&m_AssetManager);
	//sr->SetTexture(bitmap);
	//uiTrans->SetPivotPreset(TransformPivotPreset::Center, bitmap->GetSize());
	image->SetPivotPreset(ImagePivotPreset::Center, bitmap->GetSize());
	testUIObject->GetComponent<UIButtonComponent>()->Start();
	//uiTrans->SetScale({ 2.0f, 2.0f });
	

	//그래피티
	auto graffiti = std::make_shared<GraffitiObject>(m_EventDispatcher);
	graffiti->m_Name = "graffiti";
	auto graffitiTrans = graffiti->GetComponent<TransformComponent>();
	graffitiTrans->SetPosition({ 1600,900 });
	sr = graffiti->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	bitmap = m_AssetManager.LoadTexture(L"bird_texture", L"../Resource/redbird1.png");
	sr->SetPath("../Resource/redbird1.png");
	sr->SetTextureKey("bird_texture");
	sr->SetTexture(bitmap);
	sr->SetPivotPreset(SpritePivotPreset::Center, bitmap->GetSize());
	graffiti->GetComponent<GraffitiComponent>()->Start();

	AddGameObject(gameObject);
	AddGameObject(cameraObject);
	//AddGameObject(testUIObject);
	AddGameObject(graffiti);


	{
		auto obstacle = std::make_shared<Obstacle>(m_EventDispatcher);
		obstacle->m_Name = "obstacle";
		auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
		obstacleTrans->SetPosition({ 1460.0f, 350.0f });
		sr = obstacle->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
		sr->SetPath("../Resource/cat.png");
		sr->SetTextureKey("cat_texture");
		sr->SetTexture(bitmap);
		sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());

		obstacle.get()->SetZ(1);

		AddGameObject(obstacle);
	}

	{
		auto obstacle = std::make_shared<Obstacle>(m_EventDispatcher);
		obstacle->m_Name = "obstacle2";
		auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
		obstacleTrans->SetPosition({ 1000.0f, 700.0f });
		sr = obstacle->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
		sr->SetPath("../Resource/cat.png");
		sr->SetTextureKey("cat_texture");
		sr->SetTexture(bitmap);
		sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());

		obstacle.get()->SetZ(2);

		AddGameObject(obstacle);
	}


}

void TitleScene::Finalize()
{
	
}

void TitleScene::Enter()
{
}

void TitleScene::Leave()
{
}

void TitleScene::FixedUpdate()
{
	PlayerObject* player = (PlayerObject*)(m_GameObjects.find("test")->second.get()); // 나중에 플레이어로 바꿀듯
	if (player == nullptr)
		return;
	BoxColliderComponent* playerBox = player->GetComponent<BoxColliderComponent>();
	if (playerBox == nullptr)
		return;
	Vec2F playerPos = playerBox->GetCenter();
	float playerZ = player->GetZ();
	Obstacle* enemy;
	BoxColliderComponent* enemyBox;
	Vec2F enemyPos;


	for (auto gameObject : m_GameObjects)
	{
		if (player == gameObject.second.get())
			continue;
		enemyBox = gameObject.second->GetComponent<BoxColliderComponent>();
		if (enemyBox)
		{
			enemyPos = enemyBox->GetCenter();
			if (enemyPos.x < playerPos.x - 500 || enemyPos.x > playerPos.x + 500)
				continue;

			enemy = (Obstacle*)gameObject.second.get();
			float enemyZ = enemy->GetZ();
			if (enemyZ - 0.5f > playerZ || enemyZ + 0.5f < playerZ) // 질문 Z 축 검사를 먼저하는게 비용이 좋을까요 X 축 검사를 먼저하는게 비용이 좋을까요
				continue;


			if (enemyBox->BoxVsBox(*playerBox))
			{
				CollisionInfo info;
				info.self = enemyBox;
				info.other = playerBox;
				info.normal = enemyPos - playerPos;
				info.contactPoint;
				info.penetrationDepth;
				
				/*
					m_Fsm.AddState("None", noneState);
					m_Fsm.AddState("Enter", enterState);
					m_Fsm.AddState("Stay", stayState);
					m_Fsm.AddState("Exit", exitState);
				*/

				auto state = enemyBox->GetFSM().GetCurrentState();
				if (state == "None")
				{
					m_EventDispatcher.Dispatch(EventType::CollisionEnter, &info);
				}
				else if(state == "Enter")
				{
					m_EventDispatcher.Dispatch(EventType::CollisionStay, &info);
				}
				else if (state == "Stay")
				{
					m_EventDispatcher.Dispatch(EventType::CollisionStay, &info);
				}
				else if (state == "Exit")
				{
					m_EventDispatcher.Dispatch(EventType::CollisionEnter, &info);
				}
			}
			
		}
	}
}

void TitleScene::Update(float deltaTime)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Update(deltaTime);
	}

	//Math::Vector2F pos = m_Camera->GetComponent<TransformComponent>()->GetPosition();
	//m_Camera->GetComponent<TransformComponent>()->SetPosition({pos.x + 100 * deltaTime, pos.y});

	//std::cout << pos.x << " " << pos.y << std::endl;
}

void TitleScene::Render(std::vector<RenderInfo>& renderInfo)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Render(renderInfo);

		
	}
}
