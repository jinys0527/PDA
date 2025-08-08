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
#include "SoundManager.h"
#include "ButtonUI.h"
#include "UIObject.h"
#include "UIImageComponent.h"
#include "UISliderComponent.h"
#include "UIGridComponent.h"
#include "UITextComponent.h"

#include "Telegraph.h"

#include "InputManager.h"
#include "TestListener.h"
#include "PlayerObject.h"
#include "GraffitiObject.h"
#include "GraffitiComponent.h"
#include "Obstacle.h"
#include "ItemObject.h"
#include "FSM.h"
#include "FlyingObstacleComponent.h"
#include "DroneComponent.h"
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

#include "GameManager.h"


void TestScene::Initialize()
{
#pragma region telegraph
	std::vector<std::shared_ptr<Telegraph>> m_Telegraphs;
	m_Telegraphs.reserve(12); // Â¸ÃžÂ¸Ã°Â¸Â® ?Ã§Ã?�Ã’Â´Ã�?Â¹Ã¦ÃÃ¶

	const int columns = 4;
	const int rows = 3;

	const float startX = 0.0f;
	const float startY = 0.0f;

	// Â¿Â©Â¹Ã©(margin) Â¼Â³ÃÂ¤
	const float marginX = 20.0f; // Â°Â¡Â·ÃŽ Â°Â£Â°Ã
	const float marginY = 20.0f; // Â¼Â¼Â·ÃŽ Â°Â£Â°Ã

	D2D1_SIZE_F tileSize = { 0 };

	for (int i = 0; i < 12; ++i)
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

		// Â°Â£Â°Ã Ã?�Ã·Ã‡Ã�?ÃÃ?�Ã‡Â�?Â°Ã¨Â»Ãª
		float posX = startX + col * (tileSize.width + marginX);
		float posY = startY + row * (tileSize.height + marginY);

		std::cout << "posx: " << posX << " posy: " << posY << std::endl;
		teleobj->GetComponent<TransformComponent>()->SetPosition({ posX, posY });
		sr->SetOpacity(0.0f);
		teleobj->SetZ(row);

		AddGameObject(teleobj);
		m_Telegraphs.push_back(teleobj);
	}




#pragma endregion

	m_BlackBoard = std::make_unique<BossBlackBoard>(m_Telegraphs);
	m_BehaviorTree = std::make_unique<BossBehaviorTree>(*m_BlackBoard);	m_BehaviorTree->Initialize();

	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans3 = cameraObject->GetComponent<TransformComponent>();
	trans3->SetPosition({ 960.0f, 540.0f });
	//cameraObject->GetComponent<CameraComponent>()->SetZoom(0.5f);
	BoxColliderComponent* cameraCol = cameraObject->AddComponent<BoxColliderComponent>();
	cameraCol->Start();
	//cameraCol->SetSize({ 1920, 1080 });
	cameraCol->SetSize({ 2120, 1080 });
	SetMainCamera(cameraObject);

	AddGameObject(cameraObject);

	{
		auto gameObject = std::make_shared<PlayerObject>(m_EventDispatcher);
		gameObject->m_Name = "player";
		//m_EventDispatcher.AddListener()
		auto trans = gameObject->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.0f, 540.0f });
		auto sr = gameObject->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		auto& clips = m_AssetManager.LoadAnimation(L"boss", L"../Resource/Character/Boss/Boss_Arm_Right_Hit/boss.json");
		auto animComp = gameObject->AddComponent<AnimationComponent>();
		animComp->SetAssetManager(&m_AssetManager);
		gameObject->SetShadowBitmap(m_AssetManager.LoadTexture(L"cat", L"../Resource/cat.png"));

		for (const auto& [clipName, clip] : clips)
		{
			animComp->AddClip(clipName, &clip);
		}

		//sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());
		animComp->Play("attack");
		sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
		sr->SetTextureKey("boss");

		AddGameObject(gameObject);

		//±×·¡ÇÇÆ¼
		auto graffiti = std::make_shared<GraffitiObject>(m_EventDispatcher);
		graffiti->m_Name = "graffiti";
		auto graffitiTrans = graffiti->GetComponent<TransformComponent>();
		graffitiTrans->SetPosition({ 200,300 });
		sr = graffiti->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat_texture.png");
		sr->SetPath("../Resource/cat_texture.png");
		sr->SetTextureKey("cat_texture");
		sr->SetTexture(bitmap);
		sr->SetPivotPreset(SpritePivotPreset::Center, bitmap->GetSize());
		graffiti->GetComponent<GraffitiComponent>()->Start();

		graffiti->SetGravitti(&m_AssetManager);
		graffiti->SetCameraObject(GetMainCamera());

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

			obstacle->SetZ(1);
			obstacle->SetSlide(true);

			//AddGameObject(obstacle);
		}

		{
			auto obstacle = std::make_shared<ItemObject>(m_EventDispatcher);
			obstacle->m_Name = "item";
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

		{
			auto obstacle = std::make_shared<ItemObject>(m_EventDispatcher);
			obstacle->m_Name = "item2";
			auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
			obstacleTrans->SetPosition({ 1000.0f, 700.0f });
			sr = obstacle->AddComponent<SpriteRenderer>();
			sr->SetAssetManager(&m_AssetManager);
			bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
			sr->SetPath("../Resource/cat.png");
			sr->SetTextureKey("cat_texture");
			sr->SetTexture(bitmap);
			sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());

			obstacle->m_isBullet = true;

			obstacle.get()->SetZ(2);

			AddGameObject(obstacle);
		}
	}


	{
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


		//AddGameObject(gameObject);
	}

	{

		auto soundUI = std::make_shared<SoundUI>(m_SoundManager, m_EventDispatcher);
		soundUI->m_Name = "sound";
		soundUI->SetSlider();
		auto uiText = soundUI->AddComponent<UITextComponent>();
		uiText->SetDWriteFactory(m_Renderer.GetDWriteFactory());
		uiText->SetText(L"UI ÅØ½ºÆ® ¿¹½Ã");
		uiText->SetFontName(L"Segoe UI");
		uiText->SetFontSize(24.0f);
		uiText->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		uiText->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		uiText->SetLayoutSize(500.0f, 100.0f);
		m_SoundManager.BGM_Shot(L"bgm");
		m_SoundManager.SFX_Shot(L"sfx_b2b");
		m_SoundManager.UI_Shot(L"play");

		auto rect = soundUI->GetComponent<RectTransformComponent>();
		rect->SetAnchorPreset(AnchorPrset::FullStretch);
		rect->SetPivotPreset(RectTransformPivotPreset::Center);
		rect->SetPosition({ 0.0f, 0.0f });
		rect->SetSize({ 600.f, 600.f });

		auto uiObj1 = std::make_shared<UIObject>(m_EventDispatcher);
		auto uiImage1 = uiObj1->AddComponent<UIImageComponent>();
		uiImage1->SetBitmap(m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png"));
		uiImage1->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
		uiImage1->SetPivotPreset(ImagePivotPreset::Center, uiImage1->GetTexture()->GetSize());
		auto rect1 = uiObj1->GetComponent<RectTransformComponent>();
		rect1->SetAnchorPreset(AnchorPrset::FullStretch);
		rect1->SetPivotPreset(RectTransformPivotPreset::Center);
		rect1->SetSize({ 300.0f, 200.0f });
		rect1->SetPosition({ 0.0f, -410.0f });
		soundUI->GetMaster()->SetFrame(uiObj1);
		soundUI->GetMaster()->SetFill(uiObj1);

		auto uiObj2 = std::make_shared<UIObject>(m_EventDispatcher);
		auto uiImage2 = uiObj2->AddComponent<UIImageComponent>();
		uiImage2->SetBitmap(m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png"));
		uiImage2->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
		uiImage2->SetPivotPreset(ImagePivotPreset::Center, uiImage2->GetTexture()->GetSize());
		auto rect2 = uiObj2->GetComponent<RectTransformComponent>();
		rect2->SetAnchorPreset(AnchorPrset::FullStretch);
		rect2->SetPivotPreset(RectTransformPivotPreset::Center);
		rect2->SetSize({ 300.0f, 200.0f });
		rect2->SetPosition({ 0.0f, -160.0f });
		soundUI->GetBGM()->SetFrame(uiObj2);
		soundUI->GetBGM()->SetFill(uiObj2);

		auto uiObj3 = std::make_shared<UIObject>(m_EventDispatcher);
		auto uiImage3 = uiObj3->AddComponent<UIImageComponent>();
		uiImage3->SetBitmap(m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png"));
		uiImage3->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
		uiImage3->SetPivotPreset(ImagePivotPreset::Center, uiImage3->GetTexture()->GetSize());
		auto rect3 = uiObj3->GetComponent<RectTransformComponent>();
		rect3->SetAnchorPreset(AnchorPrset::FullStretch);
		rect3->SetPivotPreset(RectTransformPivotPreset::Center);
		rect3->SetSize({ 300.0f, 200.0f });
		rect3->SetPosition({ 0.0f, 00.0f });
		soundUI->GetSFX()->SetFrame(uiObj3);
		soundUI->GetSFX()->SetFill(uiObj3);

		auto uiObj4 = std::make_shared<UIObject>(m_EventDispatcher);
		auto uiImage4 = uiObj4->AddComponent<UIImageComponent>();
		uiImage4->SetBitmap(m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png"));
		uiImage4->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
		uiImage4->SetPivotPreset(ImagePivotPreset::Center, uiImage4->GetTexture()->GetSize());
		auto rect4 = uiObj4->GetComponent<RectTransformComponent>();
		rect4->SetAnchorPreset(AnchorPrset::FullStretch);
		rect4->SetPivotPreset(RectTransformPivotPreset::Center);
		rect4->SetSize({ 300.0f, 200.0f });
		rect4->SetPosition({ 0.0f, 340.0f });
		soundUI->GetUI()->SetFrame(uiObj4);
		soundUI->GetUI()->SetFill(uiObj4);
	}


		/*auto buttonUI = std::make_shared<ButtonUI>(m_EventDispatcher);
		auto uiButton = buttonUI->GetComponent<UIButtonComponent>();
		uiButton->Start();
		uiButton->GetFSM().SetOnEnter("Click", []() {std::cout << "Click" << std::endl; });
		auto uiImage5 = buttonUI->AddComponent<UIImageComponent>();
		uiImage5->SetBitmap(m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png"));
		uiImage5->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
		uiImage5->SetPivotPreset(ImagePivotPreset::Center, uiImage5->GetTexture()->GetSize());
		auto rect5 = buttonUI->GetComponent<RectTransformComponent>();
		rect5->SetAnchorPreset(AnchorPrset::FullStretch);
		rect5->SetPivotPreset(RectTransformPivotPreset::Center);
		rect5->SetSize({ 300.0f, 200.0f });
		rect5->SetPosition({ 0.0f, 0.0f });*/
		/*sr->SetPath("../Resource/cat.png");
		sr->SetTextureKey("cat_texture");*/


#pragma region Grid
	auto uiObject = std::make_shared<UIObject>(m_EventDispatcher);
	auto uiRect = uiObject->GetComponent<RectTransformComponent>();
	uiRect->SetPosition({ 0.0f, 0.0f });
	uiRect->SetAnchorPreset(AnchorPrset::FullStretch);
	uiRect->SetPivotPreset(RectTransformPivotPreset::Center);
	auto grid = uiObject->AddComponent<UIGridComponent>();
	grid->SetCellSize({ 64, 64 });
	grid->SetPadding({ 10, 10 });
	grid->SetSpacing({ 5, 5 });
	grid->SetRowColumn(1, 3); // 1�� 3��

	auto heartUI = std::make_shared<UIObject>(m_EventDispatcher);
	auto heart = heartUI->AddComponent<UIImageComponent>();
	heart->SetBitmap(m_AssetManager.LoadTexture(L"heart", "../Resource/HEART.png"));
	heart->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	heart->SetPivotPreset(ImagePivotPreset::Center, heart->GetTexture()->GetSize());
	auto rect = heartUI->GetComponent<RectTransformComponent>();
	rect->SetAnchorPreset(AnchorPrset::FullStretch);
	rect->SetPivotPreset(RectTransformPivotPreset::Center);

	grid->AddItem(heartUI);
	auto heartUI2 = std::make_shared<UIObject>(m_EventDispatcher);
	heart = heartUI2->AddComponent<UIImageComponent>();
	heart->SetBitmap(m_AssetManager.LoadTexture(L"heart", "../Resource/HEART.png"));
	heart->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	heart->SetPivotPreset(ImagePivotPreset::Center, heart->GetTexture()->GetSize());
	rect = heartUI2->GetComponent<RectTransformComponent>();
	rect->SetAnchorPreset(AnchorPrset::FullStretch);
	rect->SetPivotPreset(RectTransformPivotPreset::Center);
	grid->AddItem(heartUI2);
	auto heartUI3 = std::make_shared<UIObject>(m_EventDispatcher);
	heart = heartUI3->AddComponent<UIImageComponent>();
	heart->SetBitmap(m_AssetManager.LoadTexture(L"heart", "../Resource/HEART.png"));
	heart->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	heart->SetPivotPreset(ImagePivotPreset::Center, heart->GetTexture()->GetSize());
	rect = heartUI3->GetComponent<RectTransformComponent>();
	rect->SetAnchorPreset(AnchorPrset::FullStretch);
	rect->SetPivotPreset(RectTransformPivotPreset::Center);
	grid->AddItem(heartUI3);


	grid->UpdateLayout();

#pragma endregion



	//AddGameObject(gameObject);
  /*sr->SetTexture(bitmap);
	sr2->SetTexture(bitmap);*/
	//AddGameObject(gameObject);
	//AddGameObject(gameObject2);
	//AddUIObject(soundUI);
	//AddUIObject(buttonUI);
	AddUIObject(uiObject);


	{
		auto obstacle = std::make_shared<Obstacle>(m_EventDispatcher);
		obstacle->m_Name = "obstacle3";
		auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
		obstacleTrans->SetPosition({ 3000.0f, 350.0f });
		auto sr = obstacle->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
		sr->SetPath("../Resource/cat.png");
		sr->SetTextureKey("cat_texture");
		sr->SetTexture(bitmap);
		sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());

		obstacle->SetZ(1);
		obstacle->SetSlide(false);

		auto lambdaObstacle = obstacle.get();
		auto lambdaCamera = cameraObject.get();

		auto rect = obstacle->GetComponent<BoxColliderComponent>();
		rect->SetCenter(obstacleTrans->GetPosition());
		m_EventDispatcher.AddListener(EventType::CollisionTrigger, rect);
		rect->SetOnTrigger(
			[lambdaObstacle, lambdaCamera](const CollisionInfo& info)
			{
				if (info.self != lambdaObstacle->GetComponent<BoxColliderComponent>())
					return;
				lambdaObstacle->GetComponent<TransformComponent>()->SetParent(lambdaCamera->GetComponent<TransformComponent>());
				auto component = lambdaObstacle->AddComponent<FlyingObstacleComponent>();
				component->Start();
				lambdaObstacle->GetComponent<BoxColliderComponent>()->OnTrigger();
			}
		);



		AddGameObject(obstacle);
	}
	{
		auto obstacle = std::make_shared<GameObject>(m_EventDispatcher);
		obstacle->m_Name = "drone3";
		auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
		obstacleTrans->SetPosition({ 3000.0f, 350.0f });
		auto sr = obstacle->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
		sr->SetPath("../Resource/cat.png");
		sr->SetTextureKey("cat_texture");
		sr->SetTexture(bitmap);
		sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());

		auto lambdaObstacle = obstacle.get();
		auto lambdaCamera = cameraObject.get();

		auto rect = obstacle->AddComponent<BoxColliderComponent>();
		//m_EventDispatcher.AddListener(EventType::CollisionTrigger, rect);
		rect->SetSize({ 100, 100 });
		rect->Start();
		rect->SetOnTrigger(
			[lambdaObstacle, lambdaCamera](const CollisionInfo& info)
			{
				if (info.self != lambdaObstacle->GetComponent<BoxColliderComponent>())
					return;
				lambdaObstacle->GetComponent<TransformComponent>()->SetParent(lambdaCamera->GetComponent<TransformComponent>());
				auto component = lambdaObstacle->AddComponent<DroneComponent>();
				component->Start();
				lambdaObstacle->GetComponent<BoxColliderComponent>()->OnTrigger();
			}
		);


		AddGameObject(obstacle);
	}
	{
		auto obstacle = std::make_shared<GameObject>(m_EventDispatcher);
		obstacle->m_Name = "savepoint";
		auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
		obstacleTrans->SetPosition({ 3000.0f, 350.0f });
		auto sr = obstacle->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
		sr->SetPath("../Resource/cat.png");
		sr->SetTextureKey("cat_texture");
		sr->SetTexture(bitmap);
		sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());

		auto lambdaObstacle = obstacle.get();
		auto lambdaCamera = cameraObject.get();

		auto rect = obstacle->AddComponent<BoxColliderComponent>();
		//m_EventDispatcher.AddListener(EventType::CollisionTrigger, rect);
		rect->SetSize({ 100, 10000 });
		rect->Start();
		rect->SetOnTrigger(
			[lambdaObstacle, this](const CollisionInfo& info)
			{
				if (info.self != lambdaObstacle->GetComponent<BoxColliderComponent>())
					return;
				this->SavePlayerInfo();
			}
		);


		AddGameObject(obstacle);
	}
}

void TestScene::Finalize()
{
}

void TestScene::Enter()
{
	LoadPlayerInfo();
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
	if (m_GameObjects.find("Camera") == m_GameObjects.end())
		return;
	PlayerObject* player = (PlayerObject*)(m_GameObjects.find("player")->second.get()); // ??ì¨·????? ???ë¼±æ¿?è«?�ë¶�???
	GameObject* cameraObject = m_GameObjects.find("Camera")->second.get();

	if (player == nullptr)
		return;
	BoxColliderComponent* playerBox = player->GetComponent<BoxColliderComponent>();
	if (playerBox == nullptr)
		return;
	BoxColliderComponent* cameraBox = cameraObject->GetComponent<BoxColliderComponent>();
	BoxColliderComponent* opponentBox;
	Vec2F playerPos = playerBox->GetCenter();
	Vec2F cameraPos = cameraObject->GetComponent<BoxColliderComponent>()->GetCenter();
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
		if (cameraObject == gameObject->second.get())
			continue;
		//if (gameObject->first == "tele3")
		//{
		//	gameObject = gameObject;
		//}
		cameraObject->GetComponent<BoxColliderComponent>();

		opponentZ = -1;
		opponentBox = gameObject->second->GetComponent<BoxColliderComponent>();
		if (opponentBox)
		{
			auto state = opponentBox->GetFSM().GetCurrentState();

			opponentPos = opponentBox->GetCenter();

			if (opponentPos.x > cameraPos.x + 1500 || cameraPos.x-1500 > opponentPos.x)
			{
				continue;
			}

			if (opponentBox->BoxVsBox(*cameraBox))
			{
				CollisionInfo info;
				info.self = opponentBox;
				info.other = cameraBox;
				info.normal = opponentPos - playerPos;
				info.contactPoint;
				info.penetrationDepth;

				m_EventDispatcher.Dispatch(EventType::CollisionTrigger, &info);

			}


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
			if (opponentZ - 0.5f > playerZ || opponentZ + 0.5f < playerZ) // Ã¬Â§?Ã«Â¬Â¸ Z Ã¬Â¶?ÃªÂ²??Â¬Ã«? Ã«Â¨Â¼Ã¬???Ã«Å ?ÃªÂ?Ã«Â¹?žÃ?¡Â??Ã¬Â¢?¹Ã?â??�ÃªÂ¹Å’�?¡â??X Ã¬Â¶?ÃªÂ²??Â¬Ã«? Ã«Â¨Â¼Ã¬???Ã«Å ?ÃªÂ?Ã«Â¹?žÃ?¡Â??Ã¬Â¢?¹Ã?â??�ÃªÂ¹Å’�?¡â??
			{
				ObjectCollisionLeave(m_EventDispatcher, opponentBox, playerBox);
				continue;
			}

			if (enemy)
			{
				if (enemy->GetSlide() && player->GetSlide())
				{
					ObjectCollisionLeave(m_EventDispatcher, opponentBox, playerBox);
					continue;
				}
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
	//m_BTElapsedTime += deltaTime;
	//m_OneSecondTimer += deltaTime;

	m_GameManager->m_scrollSpeed += deltaTime;
	if (m_GameManager->m_scrollSpeed >= 500)
		m_GameManager->m_scrollSpeed = 500;

	Vec2F move = { 0, 0 };
	move.x += m_GameManager->m_scrollSpeed;
	m_GameObjects.find("Camera")->second->GetComponent<TransformComponent>()->Translate(move);
	m_GameObjects.find("player")->second->GetComponent<TransformComponent>()->Translate(move);

	//if (m_BTElapsedTime >= 0.016f)
	//{
	//	if (m_BehaviorTree)
	//	{
	//		m_BehaviorTree->Tick(m_BTElapsedTime);
	//	}

	//	m_BTElapsedTime = 0.0f;

	//}

	//if (m_OneSecondTimer >= 1.0f)
	//{
	//	m_OneSecondTimer = 0.0f;

	//	float curHP = m_BlackBoard->GetValue<float>("BossCurrHP").value();
	//	//std::cout << "Ã?�Ã�?Ã§ HP: " << curHP << std::endl;
	//	m_BlackBoard->SetValue("BossCurrHP", curHP - 5);

	//	// Â°Â¡ÃÃŸÃ?�Â�?Â·ÃŽÂ±Ã??Ã?Ã¢Â·Ã??
	//	//float w1 = m_BlackBoard->GetValue<float>("SkillWeight_1").value();
	//	//float w2 = m_BlackBoard->GetValue<float>("SkillWeight_2").value();
	//	//float w3 = m_BlackBoard->GetValue<float>("SkillWeight_3").value();

	//	//std::cout << "Skill Weights: [1] " << w1 << "  [2] " << w2 << "  [3] " << w3 << std::endl;
	//}
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Update(deltaTime);
	}
	for (auto uiObject : m_UIObjects)
	{
		uiObject.second->Update(deltaTime);
	}
}

void TestScene::Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Render(renderInfo);
	}
	for (auto uiObject : m_UIObjects)
	{
		uiObject.second->Render(uiRenderInfo);
		uiObject.second->Render(uiTextInfo);
	}
}

void TestScene::SavePlayerInfo()
{
	auto player = dynamic_cast<PlayerObject*>(m_GameObjects.find("player")->second.get());
	m_GameManager->m_playerHp = player->GetHp();
	m_GameManager->m_playerReinforcedAttack = player->GetBullet();
	m_GameManager->m_playerXLoc = player->GetComponent<TransformComponent>()->GetPosition().x+500;
}

void TestScene::LoadPlayerInfo()
{
	auto player = dynamic_cast<PlayerObject*>(m_GameObjects.find("player")->second.get());
	player->SetHp(m_GameManager->m_playerHp);
	player->SetBullet(m_GameManager->m_playerReinforcedAttack);
	player->GetComponent<TransformComponent>()->SetPosition({ m_GameManager->m_playerXLoc, 0 });
	GetMainCamera()->GetComponent<TransformComponent>()->SetPosition({ m_GameManager->m_playerXLoc+500, 540.0f });
}
