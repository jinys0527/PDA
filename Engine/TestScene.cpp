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

//----
#include "InputManager.h"
#include "TestListener.h"
#include "PlayerObject.h"
#include "ButtonUI.h"
#include "GraffitiObject.h"
#include "GraffitiComponent.h"
#include "Obstacle.h"
#include "ItemObject.h"
#include "FSM.h"
//---


//================================
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
	
	{
		m_BlackBoard = std::make_unique<BossBlackBoard>();
		m_BehaviorTree = std::make_unique<BossBehaviorTree>(*m_BlackBoard);	m_BehaviorTree->Initialize();

		auto gameObject = std::make_shared<PlayerObject>(m_EventDispatcher);
		gameObject->m_Name = "player";
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
		//±×·¡ÇÇÆ¼
		auto graffiti = std::make_shared<GraffitiObject>(m_EventDispatcher);
		graffiti->m_Name = "graffiti";
		auto graffitiTrans = graffiti->GetComponent<TransformComponent>();
		graffitiTrans->SetPosition({ 1600,900 });
		sr = graffiti->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
		sr->SetPath("../Resource/cat.png");
		sr->SetTextureKey("cat_texture");
		sr->SetTexture(bitmap);
		sr->SetPivotPreset(SpritePivotPreset::Center, bitmap->GetSize());
		graffiti->GetComponent<GraffitiComponent>()->Start();

		AddGameObject(gameObject);
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
	

	auto gameObject = std::make_shared<GameObject>(m_EventDispatcher);
	gameObject->m_Name = "test";
	auto trans = gameObject->GetComponent<TransformComponent>();
	trans->SetPosition({ 300.0f, 300.0f });
	auto sr = gameObject->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto& clips = m_AssetManager.LoadAnimation(L"boss", L"../Resource/Character/Boss/Boss_Arm_Right_Hit/boss.json");

	auto animComp = gameObject->AddComponent<AnimationComponent>();
	animComp->SetAssetManager(&m_AssetManager);

	for (const auto& [clipName, clip] : clips)
	{
		animComp->AddClip(clipName, &clip);
	}

	animComp->Play("attack");
	sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
	sr->SetTextureKey("boss");

	auto soundUI = std::make_shared<SoundUI>(m_SoundManager, m_EventDispatcher);
	soundUI->m_Name = "sound";
	auto rect = soundUI->GetComponent<RectTransformComponent>();
	rect->SetPosition({ 0.0f, 0.0f });
	auto uiImage = std::make_shared<UIImageComponent>();
	uiImage->SetBitmap(m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png"));
	soundUI->GetBGM()->SetFrame(uiImage.get());


	/*sr->SetPath("../Resource/cat.png");
	sr->SetTextureKey("cat_texture");*/

	//auto gameObject2 = std::make_shared<GameObject>(m_EventDispatcher);
	//gameObject2->m_Name = "test2";
	//auto trans2 = gameObject2->GetComponent<TransformComponent>();
	//trans2->SetPosition({ 800.0f, 500.0f });
	//auto sr2 = gameObject2->AddComponent<SpriteRenderer>();
	//sr2->SetAssetManager(&m_AssetManager);
	//sr2->SetPath("../Resource/cat.png");
	//sr2->SetTextureKey("cat_texture");

	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans3 = cameraObject->GetComponent<TransformComponent>();
	trans3->SetPosition({ 960.0f, 540.0f });
	cameraObject->GetComponent<CameraComponent>()->SetZoom(0.5f);
	SetMainCamera(cameraObject);

	/*sr->SetTexture(bitmap);
	sr2->SetTexture(bitmap);*/
	AddGameObject(gameObject);
	//AddGameObject(gameObject2);
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
	PlayerObject* player = (PlayerObject*)(m_GameObjects.find("player")->second.get()); // ??ì¨·????? …??ë¼±æ¿?è«›ë¶½???
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
			if (opponentZ - 0.5f > playerZ || opponentZ + 0.5f < playerZ) // ì§ˆë¬¸ Z ì¶?ê²€?¬ë? ë¨¼ì??˜ëŠ”ê²?ë¹„ìš©??ì¢‹ì„ê¹Œìš” X ì¶?ê²€?¬ë? ë¨¼ì??˜ëŠ”ê²?ë¹„ìš©??ì¢‹ì„ê¹Œìš”
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
		//std::cout << "ÇöÀç HP: " << curHP << std::endl;
		m_BlackBoard->SetValue("BossCurrHP", curHP - 5);

		// °¡ÁßÄ¡ ·Î±× Ãâ·Â
		//float w1 = m_BlackBoard->GetValue<float>("SkillWeight_1").value();
		//float w2 = m_BlackBoard->GetValue<float>("SkillWeight_2").value();
		//float w3 = m_BlackBoard->GetValue<float>("SkillWeight_3").value();

		//std::cout << "Skill Weights: [1] " << w1 << "  [2] " << w2 << "  [3] " << w3 << std::endl;
	}

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
