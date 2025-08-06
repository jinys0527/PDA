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
#include "ItemObject.h"
#include "AnimationComponent.h"
#include "FSM.h"

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
		auto obstacle = std::make_shared<ItemObject>(m_EventDispatcher);
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

void ObjectCollisionLeave(EventDispatcher &eventDispatcher, BoxColliderComponent *enemy, BoxColliderComponent* player)
{
	if (enemy->GetFSM().GetCurrentState() == "None")
		return;

	CollisionInfo info;
	info.self = enemy;
	info.other = player;
	info.normal;
	info.contactPoint;
	info.penetrationDepth;

	eventDispatcher.Dispatch(EventType::CollisionExit, &info);
}

void TitleScene::FixedUpdate()
{
	PlayerObject* player = (PlayerObject*)(m_GameObjects.find("test")->second.get()); // 나중에 플레이어로 바꿀듯
	if (player == nullptr)
		return;
	BoxColliderComponent* playerBox = player->GetComponent<BoxColliderComponent>();
	if (playerBox == nullptr)
		return;
	BoxColliderComponent* opponentBox;
	Vec2F playerPos = playerBox->GetCenter();
	Vec2F opponentPos;
	float playerZ = player->GetZ();
	float opponentZ;
	Obstacle* enemy = nullptr;
	ItemObject* ally = nullptr;

	std::list<std::shared_ptr<GameObject>> removeList;



	for (auto gameObject = m_GameObjects.begin(); gameObject != m_GameObjects.end(); gameObject++)
	{
		auto something = gameObject->second.get();
		if (player == gameObject->second.get())
			continue;
		opponentZ = -1;
		opponentBox = gameObject->second->GetComponent<BoxColliderComponent>();
		if (opponentBox)
		{
			auto state = opponentBox->GetFSM().GetCurrentState();

			opponentPos = opponentBox->GetCenter();

			if (opponentPos.x < playerPos.x - 500 || opponentPos.x > playerPos.x + 500)
			{
				continue;
			}

			if (enemy = dynamic_cast<Obstacle*>(gameObject->second.get()))
				opponentZ = enemy->GetZ();
			else if (ally = dynamic_cast<ItemObject*>(gameObject->second.get()))
				opponentZ = ally->GetZ();
			else
				continue;
			if (opponentZ - 0.5f > playerZ || opponentZ + 0.5f < playerZ) // 질문 Z 축 검사를 먼저하는게 비용이 좋을까요 X 축 검사를 먼저하는게 비용이 좋을까요
			{
				ObjectCollisionLeave(m_EventDispatcher, opponentBox, playerBox);
				continue;
			}


			if (opponentBox->BoxVsBox(*playerBox))
			{
				CollisionInfo info;
				info.self = opponentBox;
				info.other = playerBox;
				info.normal = opponentPos - playerPos;
				info.contactPoint;
				info.penetrationDepth;
			

				
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

				if (ally)
				{
					removeList.push_back(gameObject->second);
					//RemoveGameObject(gameObject->second);
					//m_GameObjects.erase(gameObject->first);
					//gameObject--;
				}
				continue;
			}

			ObjectCollisionLeave(m_EventDispatcher, opponentBox, playerBox);
		}
	}

	for (auto it = removeList.begin(); it != removeList.end(); ++it)
	{
		RemoveGameObject(*it);
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
