#include "pch.h"
#include "TestScene.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "CameraObject.h"
#include "CameraComponent.h"
#include "AnimationComponent.h"
#include "AnimationController.h"
#include "SoundUI.h"
#include "UIImageComponent.h"
#include "UISliderComponent.h"
#include "Telegraph.h"
#include "Background.h"
#include "InputManager.h"
#include "TestListener.h"
#include "PlayerObject.h"
#include "ButtonUI.h"
#include "GraffitiObject.h"
#include "GraffitiComponent.h"
#include "Obstacle.h"
#include "ItemObject.h"
#include "FSM.h"
//=======================
#include "BlackBoard.h"
#include "TestNode.h"
#include "Sequence.h"
#include "Selector.h"
#include "Repeater.h"
#include "Inverter.h"

//================================
#include "BossBehaviorTree.h"
#include "BossBlackBoard.h"
//================================


void TestScene::Initialize()
{
#pragma region camera
	auto soundUI = std::make_shared<SoundUI>(m_SoundManager, m_EventDispatcher);
	soundUI->m_Name = "sound";
	auto rect = soundUI->GetComponent<RectTransformComponent>();
	rect->SetPosition({ 0.0f, 0.0f });
	auto uiImage = std::make_shared<UIImageComponent>();
	uiImage->SetBitmap(m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png"));
	soundUI->GetBGM()->SetFrame(uiImage.get());

	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans3 = cameraObject->GetComponent<TransformComponent>();
	trans3->SetPosition({ 60.0f, 540.f });
	cameraObject->GetComponent<CameraComponent>()->SetZoom(1.0f);
	SetMainCamera(cameraObject);

#pragma endregion

#pragma region anim
	std::vector<std::shared_ptr<GameObject>> m_Anims;



	auto bossarm = std::make_shared<GameObject>(m_EventDispatcher);
	bossarm->m_Name = "BossArm";
	auto trans2 = bossarm->GetComponent<TransformComponent>();
	trans2->SetPosition({ 960, 540 });
	auto sr2 = bossarm->AddComponent<SpriteRenderer>();
	sr2->SetAssetManager(&m_AssetManager);

	auto& clips = m_AssetManager.LoadAnimation(L"boss", L"../Resource/Character/Boss/Boss_Arm_Right_Hit/boss.json");
	auto anim = bossarm->AddComponent<AnimationComponent>();
	anim->SetAssetManager(&m_AssetManager);
	for (const auto& [clipName, clip] : clips)
	{
		anim->AddClip(clipName, &clip);
	}

	anim->Play("attack");
	anim->SetLoop(false);
	anim->SetIsActive(false);

	sr2->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
	sr2->SetTextureKey("boss");
	
	sr2->SetPivotPreset(SpritePivotPreset::BottomRight, {960, 800});

	m_Anims.push_back(bossarm);
 	AddGameObject(bossarm);

#pragma endregion

#pragma region telegraph
	std::vector<std::shared_ptr<Telegraph>> m_Telegraphs;
	m_Telegraphs.reserve(12);

	const int columns = 5;
	const int rows = 3;

	const float startX = 300.0f;
	const float startY = 300.0f;

	const float marginX = 20.0f;
	const float marginY = 20.0f;

	D2D1_SIZE_F tileSize = { 0 };

	for (int i = 0; i < columns * rows; ++i)
	{
		auto teleobj = std::make_shared<Telegraph>(m_EventDispatcher);
		teleobj->m_Name = "tele" + std::to_string(i);
		auto sr = teleobj->AddComponent<SpriteRenderer>();
		auto texture = m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png");
		sr->SetTexture(texture);
		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());

		if (i == 0)
		{
			tileSize = texture->GetSize();
		}

		int col = i % columns;
		int row = i / columns;

		float posX = startX + col * (tileSize.width + marginX);
		float posY = startY + row * (tileSize.height + marginY);

		std::cout << "posx: " << posX << " posy: " << posY << std::endl;
		teleobj->GetComponent<TransformComponent>()->SetPosition({ posX, posY });
		sr->SetOpacity(0.0f);

		AddGameObject(teleobj);
		m_Telegraphs.push_back(teleobj);
	}
 
	m_BlackBoard = std::make_unique<BossBlackBoard>(m_Telegraphs, m_Anims);
	m_BehaviorTree = std::make_unique<BossBehaviorTree>(*m_BlackBoard);	m_BehaviorTree->Initialize();
#pragma endregion

	

#pragma region Background
	//auto back1 = std::make_shared<Background>(m_EventDispatcher);
	//back1->m_Name = "back1";
	//auto backtr1 = back1->GetComponent<TransformComponent>();
	//backtr1->SetPosition({ 0, 540 });
	//auto backimage1 = m_AssetManager.LoadTexture(L"백그라운드", L"../Resource/Background/백그라운드.png");
	//auto backsr1 = back1->AddComponent<SpriteRenderer>();
	//backsr1->SetAssetManager(&m_AssetManager);
	//backsr1->SetTexture(backimage1);
	//backsr1->SetPivotPreset(SpritePivotPreset::Center, backimage1->GetSize());

	//AddGameObject(back1);

	//auto back2 = std::make_shared<Background>(m_EventDispatcher);
	//back2->m_Name = "back2";
	//auto backtr2 = back2->GetComponent<TransformComponent>();
	//backtr2->SetPosition({ backimage1->GetSize().width, 540});
	//auto backsr2 = back2->AddComponent<SpriteRenderer>();
	//backsr2->SetAssetManager(&m_AssetManager);
	//backsr2->SetTexture(backimage1);
	//backsr2->SetPivotPreset(SpritePivotPreset::Center, backimage1->GetSize());

	//AddGameObject(back2);

	//auto back3 = std::make_shared<Background>(m_EventDispatcher);
	//back3->m_Name = "back3";
	//back3->SetMoveSpeed(3000.f);
	//auto backtr3 = back3->GetComponent<TransformComponent>();
	//backtr3->SetPosition({ 0, 0 });
	//auto backimage3 = m_AssetManager.LoadTexture(L"background", L"../Resource/Background/background.png");
	//auto backsr3 = back3->AddComponent<SpriteRenderer>();
	//backsr3->SetAssetManager(&m_AssetManager);
	//backsr3->SetTexture(backimage3);
	//backsr3->SetPivotPreset(SpritePivotPreset::Center, backimage3->GetSize());

	//AddGameObject(back3);

	//auto back4 = std::make_shared<Background>(m_EventDispatcher);
	//back4->m_Name = "back4";
	//back4->SetMoveSpeed(3000.f);
	//auto backtr4 = back4->GetComponent<TransformComponent>();
	//backtr4->SetPosition({ backimage3->GetSize().width, 0 });
	//auto backsr4 = back4->AddComponent<SpriteRenderer>();
	//backsr4->SetAssetManager(&m_AssetManager);
	//backsr4->SetTexture(backimage3);
	//backsr4->SetPivotPreset(SpritePivotPreset::Center, backimage3->GetSize());

	//AddGameObject(back4);

#pragma endregion



	AddUIObject(soundUI);
	AddGameObject(cameraObject);
}

void TestScene::Finalize()
{
}

void TestScene::Enter()
{
}

void TestScene::Leave()
{
}

void ObjectCollisionLeave(EventDispatcher& eventDispatcher, BoxColliderComponent* enemy, BoxColliderComponent* player)
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

void TestScene::FixedUpdate()
{

	if (m_GameObjects.find("player") == m_GameObjects.end())
		return;
	PlayerObject* player = (PlayerObject*)(m_GameObjects.find("player")->second.get());
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
			if (opponentZ - 0.5f > playerZ || opponentZ + 0.5f < playerZ) 
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
				else if (state == "Enter")
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

void TestScene::Update(float deltaTime)
{
#pragma region BT
	m_BTElapsedTime += deltaTime;
	m_OneSecondTimer += deltaTime;

	if (m_BTElapsedTime >= 0.016f)
	{
		if (m_BehaviorTree)
		{
			m_BehaviorTree->Tick(m_BTElapsedTime);
		}

		m_BTElapsedTime = 0.0f;

	}

	if (m_OneSecondTimer >= 1.0f)
	{
		m_OneSecondTimer = 0.0f;

		float curHP = m_BlackBoard->GetValue<float>("BossCurrHP").value();
		m_BlackBoard->SetValue("BossCurrHP", curHP - 1);

	}

#pragma endregion

	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Update(deltaTime);
	}
	for (auto uiObject : m_UIObjects)
	{
		uiObject.second->Update(deltaTime);
	}
}

void TestScene::Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Render(renderInfo);
	}
	for (auto uiObject : m_UIObjects)
	{
		uiObject.second->Render(uiRenderInfo);
	}
}
