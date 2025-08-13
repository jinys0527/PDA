#include "pch.h"
#include "GameScene.h"
#include "InputManager.h"
#include "ControlComponent.h"
#include "ButtonUI.h"
#include "GameObject.h"
#include "UIObject.h"
#include "SceneManager.h"
#include "CameraObject.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "RectTransformComponent.h"
#include "FixedObstacle_1.h"
#include "FixedObstacle_2.h"
#include "FallingObstacle_Box.h"
#include "FallingObstacle_Flowerpot.h"
#include "SlidingObstacle.h"
#include "Drone.h"
#include "ItemObject.h"
#include "SpriteRenderer.h"
#include "GraffitiObject.h"
#include "BoxColliderComponent.h"
#include <fstream>
#include "SoundUI.h"
#include "UIImageComponent.h"
#include "ChapterBackgroundManager.h"
#include "Background.h"
#include <iostream>

void GameScene::Initialize()
{
#pragma region Garbage_bag
	for (int i = 0; i < 144; i++)
	{
		auto obstacle = std::make_shared<FixedObstacle_1>(m_EventDispatcher);
		obstacle->m_Name = "Obstacle" + std::format("{:03}", i); // C++20
		obstacle->Start(&m_AssetManager);
		auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
		obstacleTrans->SetZOrder(0);
		AddGameObject(obstacle);
	}
#pragma endregion

#pragma region Wastebasket
	for (int i = 0; i < 96; i++)
	{
		auto wasteBasket = std::make_shared<FixedObstacle_2>(m_EventDispatcher);
		wasteBasket->m_Name = "WasteBasket" + std::format("{:03}", i);
		wasteBasket->Start(&m_AssetManager);
		auto wasteBasketTrans = wasteBasket->GetComponent<TransformComponent>();
		wasteBasketTrans->SetZOrder(0);
		AddGameObject(wasteBasket);
	}
#pragma endregion

#pragma region Sliding
	for (int i = 0; i < 73; i++)
	{
		auto slidingObstacle = std::make_shared<SlidingObstacle>(m_EventDispatcher);
		slidingObstacle->m_Name = "SlidingObstacle" + std::format("{:03}", i);
		slidingObstacle->Start(&m_AssetManager);
		auto slidingObstacleTrans = slidingObstacle->GetComponent<TransformComponent>();
		slidingObstacleTrans->SetZOrder(0);
		AddGameObject(slidingObstacle);
	}
#pragma endregion

#pragma region Item
	for (int i = 0; i < 11; i++)
	{
		auto item = std::make_shared<ItemObject>(m_EventDispatcher);
		item->m_Name = "Item" + std::format("{:03}", i);
		auto sr = item->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetTexture(m_AssetManager.LoadTexture(L"Candy", "../Resource/Obstacle/Candy.png"));
		sr->SetPivotPreset(SpritePivotPreset::BottomCenter, sr->GetTexture()->GetSize());
		sr->SetTextureKey("Candy");
		sr->SetPath("../Resource/Obstacle/Candy.png");
		auto itemTrans = item->GetComponent<TransformComponent>();
		itemTrans->SetZOrder(0);
		AddGameObject(item);
	}
#pragma endregion

#pragma region Drone
	for (int i = 0; i < 38; i++)
	{
		auto drone = std::make_shared<Drone>(m_EventDispatcher);
		drone->m_Name = "Drone" + std::format("{:03}", i);
		drone->Start(&m_AssetManager);
		auto droneTrans = drone->GetComponent<TransformComponent>();
		droneTrans->SetZOrder(0);
		AddGameObject(drone);
	}
#pragma endregion

#pragma region Box
	for (int i = 0; i < 24; i++)
	{
		auto box = std::make_shared<FallingObstacle_Box>(m_EventDispatcher);
		box->m_Name = "Box" + std::format("{:03}", i);
		box->Start(&m_AssetManager);
		auto boxTrans = box->GetComponent<TransformComponent>();
		boxTrans->SetZOrder(0);
		AddGameObject(box);
	}
#pragma endregion

#pragma region flowerpot
	for (int i = 0; i < 14; i++)
	{
		auto flowerpot = std::make_shared<FallingObstacle_Flowerpot>(m_EventDispatcher);
		flowerpot->m_Name = "Flowerpot" + std::format("{:03}", i);
		flowerpot->Start(&m_AssetManager);
		auto flowerpotTrans = flowerpot->GetComponent<TransformComponent>();
		flowerpotTrans->SetZOrder(0);
		AddGameObject(flowerpot);
	}
#pragma endregion

#pragma region graffiti
	for (int i = 0; i < 20; i++)
	{
		auto graffiti = std::make_shared<GraffitiObject>(m_EventDispatcher);
		graffiti->m_Name = "Graffiti" + std::format("{:03}", i);
		if (i <= 11)
		{
			graffiti->SetGravittis(&m_AssetManager, 1);
			graffiti->Start(&m_AssetManager, 1);
		}
		else
		{
			graffiti->SetGravittis(&m_AssetManager, 2);
			graffiti->Start(&m_AssetManager, 2);
		}
		auto graffitiTrans = graffiti->GetComponent<TransformComponent>();
		graffitiTrans->SetZOrder(-1);
		AddGameObject(graffiti);
	}
#pragma endregion

	//m_ChapterBackgroundManager = std::make_shared<ChapterBackgroundManager>(&m_AssetManager, m_EventDispatcher);
	//m_ChapterBackgroundManager->m_Name = "chapterBackgroundManager";
	//m_ChapterBackgroundManager->LoadBackgroundSet(1);

	//for (auto& bg : m_ChapterBackgroundManager->GetAllBackgrounds())
	//{
	//	AddGameObject(bg);
	//}

	//AddGameObject(m_ChapterBackgroundManager);

#pragma region BackGround_1
	for (int i = 1; i <= 22; i++)
	{
		auto backGround = std::make_shared<GameObject>(m_EventDispatcher);
		backGround->m_Name = "backGround" + std::to_string(i);
		auto backGroundTrans = backGround->GetComponent<TransformComponent>();
		float position_x = 4702.53f + (9405.06f * (i - 1));
		backGroundTrans->SetScale({ 0.98f, 0.98f });
		backGroundTrans->SetPosition({ position_x, 0.0f });
		auto sr = backGround->AddComponent<SpriteRenderer>();
		std::wstring key = L"Building" + std::to_wstring(i % 5 + 1);
		std::wstring path = L"../Resource/Background/Chapter1/Building" + std::to_wstring(i % 5 + 1) + L".png";
		sr->SetTexture(m_AssetManager.LoadTexture(key, path));
		sr->SetPivotPreset(SpritePivotPreset::BottomCenter, sr->GetTexture()->GetSize());
		AddGameObject(backGround);
	}

#pragma endregion

#pragma region BackGround_2
	for (int i = 1; i <= 25; i++)
	{
		auto backGround = std::make_shared<GameObject>(m_EventDispatcher);
		backGround->m_Name = "backGround2_" + std::to_string(i);
		auto backGroundTrans = backGround->GetComponent<TransformComponent>();
		float position_x = 225134.04f + (7526.4f * (i - 1));
		backGroundTrans->SetScale({ 0.98f, 0.98f });
		backGroundTrans->SetPosition({ position_x, 0.0f });
		auto sr = backGround->AddComponent<SpriteRenderer>();
		std::wstring key = L"Background" + std::to_wstring(i % 2 + 1);
		std::wstring path = L"../Resource/Background/Chapter2/Background" + std::to_wstring(i % 2 + 1) + L".png";
		sr->SetTexture(m_AssetManager.LoadTexture(key, path));
		sr->SetPivotPreset(SpritePivotPreset::BottomCenter, sr->GetTexture()->GetSize());
		AddGameObject(backGround);
	}

#pragma endregion

#pragma region Camera
	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans = cameraObject->GetComponent<TransformComponent>();
	trans->SetPosition({ 960.0f, 540.0f });
	cameraObject->GetComponent<CameraComponent>()->SetZoom(1.0f);
	BoxColliderComponent* cameraCol = cameraObject->AddComponent<BoxColliderComponent>();
	cameraCol->Start();
	cameraCol->SetSize({ 1920, 1080 });
	SetMainCamera(cameraObject);

	AddGameObject(cameraObject);
#pragma endregion
}

void GameScene::Finalize()
{
	m_UIManager.GetUIObjects().erase("GameScene");
}

void GameScene::Enter()
{
	nlohmann::json j;
	std::string fileName = GetName() + ".json";
	std::ifstream ifs(fileName);
	ifs >> j;
	Deserialize(j);

#pragma region Garbage_bag
	for (int i = 0; i < 144; i++)
	{
		auto name = "Obstacle" + std::format("{:03}", i); // C++20
		auto obstacle = dynamic_cast<Obstacle*>((m_GameObjects[name]).get());
		auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
		obstacleTrans->SetZOrder(5 - (2 * obstacle->GetZ()));
	}
#pragma endregion

#pragma region Wastebasket
	for (int i = 0; i < 96; i++)
	{
		auto name = "WasteBasket" + std::format("{:03}", i);
		auto wasteBasket = dynamic_cast<Obstacle*>((m_GameObjects[name]).get());
		auto wasteBasketTrans = wasteBasket->GetComponent<TransformComponent>();
		wasteBasketTrans->SetZOrder(5 - (2 * wasteBasket->GetZ()));
	}
#pragma endregion

#pragma region Sliding
	for (int i = 0; i < 73; i++)
	{
		auto name = "SlidingObstacle" + std::format("{:03}", i);
		auto slidingObstacle = dynamic_cast<Obstacle*>((m_GameObjects[name]).get());
		auto slidingObstacleTrans = slidingObstacle->GetComponent<TransformComponent>();
		slidingObstacleTrans->SetZOrder(5 - (2 * slidingObstacle->GetZ()));
	}
#pragma endregion

#pragma region Item
	for (int i = 0; i < 11; i++)
	{
		auto name = "Item" + std::format("{:03}", i);
		auto item = dynamic_cast<ItemObject*>((m_GameObjects[name]).get());
		auto itemTrans = item->GetComponent<TransformComponent>();
		itemTrans->SetZOrder(5 - (2 * item->GetZ()));
	}
#pragma endregion

#pragma region Box
	for (int i = 0; i < 24; i++)
	{
		auto name = "Box" + std::format("{:03}", i);
		auto box = dynamic_cast<Obstacle*>((m_GameObjects[name]).get());
		auto boxTrans = box->GetComponent<TransformComponent>();
		boxTrans->SetZOrder(5 - (2 * box->GetZ()));
	}
#pragma endregion

#pragma region flowerpot
	for (int i = 0; i < 14; i++)
	{
		auto name = "Flowerpot" + std::format("{:03}", i);
		auto flowerpot = dynamic_cast<Obstacle*>((m_GameObjects[name]).get());
		auto flowerpotTrans = flowerpot->GetComponent<TransformComponent>();
		flowerpotTrans->SetZOrder(5 - (2 * flowerpot->GetZ()));
	}
#pragma endregion
}

void GameScene::Leave()
{
}

void GameScene::FixedUpdate()
{
}

void GameScene::Update(float deltaTime)
{
	for (auto& pair : m_GameObjects)
	{
		auto& gameObject = pair.second;
		if (gameObject->IsInView(m_Camera))
		{
			gameObject->Update(deltaTime);
		}
	}

	if (m_ChapterBackgroundManager)
	{
		m_ChapterBackgroundManager->Update(deltaTime, GetMainCamera());
	}

	m_UIManager.Update(deltaTime);
}

void GameScene::Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo)
{
	if (!m_UIManager.IsFullScreenUIActive())
	{
		for (auto& pair : m_GameObjects)
		{
			auto& gameObject = pair.second;
			if (gameObject->IsInView(m_Camera))
			{
				gameObject->Render(renderInfo);
			}
		}
	}

	m_UIManager.Render(uiRenderInfo, uiTextInfo);
}