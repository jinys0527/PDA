#include "pch.h"
#include "InGameUITestScene.h"
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
#include "Background.h"
#include "InputManager.h"
#include "TestListener.h"
#include "PlayerObject.h"
#include "GraffitiObject.h"
#include "GraffitiComponent.h"
#include "Obstacle.h"
#include "ItemObject.h"
#include "FSM.h"
#include "FlyingObstacleComponent.h"
#include "PlayerEffectComponent.h"
#include "DroneComponent.h"
#include "HeartUIComponent.h"
#include "BulletUIComponent.h"
#include "BlackBoard.h"
#include "TestNode.h"
#include "Sequence.h"
#include "Selector.h"
#include "Repeater.h"
#include "Inverter.h"
#include "BossBehaviorTree.h"
#include "BossBlackBoard.h"

#include "GameManager.h"

void InGameUITestScene::Initialize()
{

#pragma region camera

	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans3 = cameraObject->GetComponent<TransformComponent>();
	trans3->SetPosition({ 60.0f, 540.f });
	cameraObject->GetComponent<CameraComponent>()->SetZoom(1.0f);
	BoxColliderComponent* cameraCol = cameraObject->AddComponent<BoxColliderComponent>();
	cameraCol->Start();
	//cameraCol->SetSize({ 1920, 1080 });
	cameraCol->SetSize({ 2120, 1080 });

	AddGameObject(cameraObject);

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

	sr2->SetPivotPreset(SpritePivotPreset::BottomRight, { 960, 800 });

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


	{
		auto gameObject = std::make_shared<PlayerObject>(m_EventDispatcher);
		gameObject->m_Name = "player";
		auto trans = gameObject->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.0f, 540.0f });
		auto sr = gameObject->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		auto animComp = gameObject->AddComponent<AnimationComponent>();
		animComp->SetAssetManager(&m_AssetManager);
		gameObject->SetShadowBitmap(m_AssetManager.LoadTexture(L"cat", L"../Resource/cat.png"));

		{
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Run_Ani", L"../Resource/Character/Sour/Sour_Run_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Attack_Ani", L"../Resource/Character/Sour/Sour_Attack_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Charge_Ani", L"../Resource/Character/Sour/Sour_Charge_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Charge_Shot_Ani", L"../Resource/Character/Sour/Sour_Charge_Shot_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Dead_Ani", L"../Resource/Character/Sour/Sour_Dead_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Heal_Ani", L"../Resource/Character/Sour/Sour_Heal_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Hitted_ani", L"../Resource/Character/Sour/Sour_Hitted_ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Jump_Ani", L"../Resource/Character/Sour/Sour_Jump_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Jump_Down_Ani", L"../Resource/Character/Sour/Sour_Jump_Down_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Jump_Top_Ani", L"../Resource/Character/Sour/Sour_Jump_Top_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Jump_Up_Ani", L"../Resource/Character/Sour/Sour_Jump_Up_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Kick_Ground_Ani", L"../Resource/Character/Sour/Sour_Kick_Ground_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Marking_Fail_Ani", L"../Resource/Character/Sour/Sour_Marking_Fail_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Marking_Success_Ani", L"../Resource/Character/Sour/Sour_Marking_Success_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Slide_Ani", L"../Resource/Character/Sour/Sour_Slide_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
			{
				auto& clips = m_AssetManager.LoadAnimation(L"Sour_Run_Ani", L"../Resource/Character/Sour/Sour_Run_Ani.json");
				for (const auto& [clipName, clip] : clips)
				{
					animComp->AddClip(clipName, &clip);
				}
			}
		}
		animComp->Play("run");
		sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
		sr->SetTextureKey("boss");
		gameObject->SetCameraObject(GetMainCamera());

		AddGameObject(gameObject);

		{
			auto effect = std::make_shared<GameObject>(m_EventDispatcher);
			effect->m_Name = "PlayerEffect";
			auto effecttrans = effect->GetComponent<TransformComponent>();
			effecttrans->SetParent(trans);
			effecttrans->SetPosition({ 0, 0 });
			auto effectsr = effect->AddComponent<SpriteRenderer>();
			effectsr->SetAssetManager(&m_AssetManager);

			auto& effectclips = m_AssetManager.LoadAnimation(L"Sour_Heal_Ani", L"../Resource/Character/Sour/Sour_Heal_Ani.json");
			auto effectanim = effect->AddComponent<AnimationComponent>();
			effectanim->SetAssetManager(&m_AssetManager);
			for (const auto& [clipName, clip] : effectclips)
			{
				effectanim->AddClip(clipName, &clip);
			}

			effectanim->Play("heal");
			effectanim->SetLoop(false);
			effectanim->Finish();

			effectsr->SetPath("../Resource/Character/Sour/Sour_Heal_Ani.json");
			effectsr->SetTextureKey("Sour_Heal_Ani");


			effectsr->SetPivotPreset(SpritePivotPreset::HealPivot, { 400, 400 });

			auto effectComp = effect->AddComponent<PlayerEffectComponent>();
			effectComp->Start();

			AddGameObject(effect);
		}


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

		AddGameObject(graffiti);
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


#pragma region soundUI
	auto soundUI = std::make_shared<SoundUI>(m_SoundManager, m_EventDispatcher);
	soundUI->m_Name = "sound";
	soundUI->SetSlider();
	auto uiText = soundUI->AddComponent<UITextComponent>();
	uiText->SetDWriteFactory(m_Renderer.GetDWriteFactory());
	uiText->SetText(L"UI 굳굳");
	uiText->SetFontName(L"Segoe UI");
	uiText->SetFontSize(24.0f);
	uiText->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	uiText->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	uiText->SetLayoutSize(500.0f, 100.0f);
	m_SoundManager.BGM_Shot(L"bgm");
	m_SoundManager.SFX_Shot(L"sfx_b2b");
	m_SoundManager.UI_Shot(L"play");
	soundUI->AddComponent<BulletUIComponent>()->Start();


	auto rect = soundUI->GetComponent<RectTransformComponent>();
	rect->SetAnchorPreset(AnchorPrset::FullStretch);
	rect->SetPivotPreset(RectTransformPivotPreset::Center);
	rect->SetPosition({ 0.0f, 0.0f });
	rect->SetSize({ 600.f, 600.f });

	// 		auto uiObj1 = std::make_shared<UIObject>(m_EventDispatcher);
	// 		auto uiImage1 = uiObj1->AddComponent<UIImageComponent>();
	// 		uiImage1->SetBitmap(m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png"));
	// 		uiImage1->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	// 		uiImage1->SetPivotPreset(ImagePivotPreset::Center, uiImage1->GetTexture()->GetSize());
	// 		auto rect1 = uiObj1->GetComponent<RectTransformComponent>();
	// 		rect1->SetAnchorPreset(AnchorPrset::FullStretch);
	// 		rect1->SetPivotPreset(RectTransformPivotPreset::Center);
	// 		rect1->SetSize({ 300.0f, 200.0f });
	// 		rect1->SetPosition({ 0.0f, -410.0f });
	// 		soundUI->GetMaster()->SetFrame(uiObj1);
	// 		soundUI->GetMaster()->SetFill(uiObj1);

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
	rect3->SetPosition({ 0.0f, 40.0f });
	soundUI->GetSFX()->SetFrame(uiObj3);
	soundUI->GetSFX()->SetFill(uiObj3);

	//m_UIManager.AddUI("InGameUITestScene", soundUI);

#pragma endregion





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
	grid->SetRowColumn(1, 3); // 1Çà 3¿­

	auto heartUI = std::make_shared<UIObject>(m_EventDispatcher);
	auto heart = heartUI->AddComponent<UIImageComponent>();
	heart->SetBitmap(m_AssetManager.LoadTexture(L"heart", "../Resource/HEART.png"));
	heart->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	heart->SetPivotPreset(ImagePivotPreset::Center, heart->GetTexture()->GetSize());
	auto rect6 = heartUI->GetComponent<RectTransformComponent>();
	rect6->SetAnchorPreset(AnchorPrset::FullStretch);
	rect6->SetPivotPreset(RectTransformPivotPreset::Center);
	grid->AddItem(heartUI);
	auto heartUIComp = heartUI->AddComponent<HeartUIComponent>();
	heartUIComp->Start();
	heartUIComp->SetHpLoc(0);

	auto heartUI2 = std::make_shared<UIObject>(m_EventDispatcher);
	heart = heartUI2->AddComponent<UIImageComponent>();
	heart->SetBitmap(m_AssetManager.LoadTexture(L"heart", "../Resource/HEART.png"));
	heart->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	heart->SetPivotPreset(ImagePivotPreset::Center, heart->GetTexture()->GetSize());
	rect6 = heartUI2->GetComponent<RectTransformComponent>();
	rect6->SetAnchorPreset(AnchorPrset::FullStretch);
	rect6->SetPivotPreset(RectTransformPivotPreset::Center);
	grid->AddItem(heartUI2);
	heartUIComp = heartUI2->AddComponent<HeartUIComponent>();
	heartUIComp->Start();
	heartUIComp->SetHpLoc(1);

	auto heartUI3 = std::make_shared<UIObject>(m_EventDispatcher);
	heart = heartUI3->AddComponent<UIImageComponent>();
	heart->SetBitmap(m_AssetManager.LoadTexture(L"heart", "../Resource/HEART.png"));
	heart->SetUV({ 0.0f, 0.0f, 300.0f, 200.0f });
	heart->SetPivotPreset(ImagePivotPreset::Center, heart->GetTexture()->GetSize());
	rect6 = heartUI3->GetComponent<RectTransformComponent>();
	rect6->SetAnchorPreset(AnchorPrset::FullStretch);
	rect6->SetPivotPreset(RectTransformPivotPreset::Center);
	grid->AddItem(heartUI3);
	heartUIComp = heartUI3->AddComponent<HeartUIComponent>();
	heartUIComp->Start();
	heartUIComp->SetHpLoc(2);


	grid->UpdateLayout();

	//m_UIManager.AddUI(buttonUI);
	//m_UIManager.AddUI("InGameUITestScene", uiObject);

#pragma endregion



	//AddGameObject(gameObject);
  /*sr->SetTexture(bitmap);
	sr2->SetTexture(bitmap);*/
	//AddGameObject(gameObject);
	//AddGameObject(gameObject2);

	AddGameObject(cameraObject);



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
		rect->SetSize({ 100, 10000 });
		rect->Start();
		rect->SetOnTrigger(
			[lambdaObstacle, this](const CollisionInfo& info)
			{
				if (info.self != lambdaObstacle->GetComponent<BoxColliderComponent>())
					return;
				this->SavePlayerInfo();
				lambdaObstacle->GetComponent<BoxColliderComponent>()->OnTrigger();
			}
		);


		AddGameObject(obstacle);
	}
}

void InGameUITestScene::Finalize()
{
}

void InGameUITestScene::Enter()
{
	LoadPlayerInfo();
}

void InGameUITestScene::Leave()
{
}

void InGameUITestScene::FixedUpdate()
{
}

void InGameUITestScene::Update(float deltaTime)
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


		m_GameManager->m_scrollSpeed += deltaTime*500;
		if (m_GameManager->m_scrollSpeed >= 2000)
		m_GameManager->m_scrollSpeed = 2000;

		Vec2F move = { 0, 0 };
		move.x += m_GameManager->m_scrollSpeed * deltaTime;
		//m_GameObjects.find("Camera")->second->GetComponent<TransformComponent>()->Translate(move);
		//m_GameObjects.find("player")->second->GetComponent<TransformComponent>()->Translate(move);


		//	m_BTElapsedTime = 0.0f;

		//}

		//if (m_OneSecondTimer >= 1.0f)
		//{
		//	m_OneSecondTimer = 0.0f;
		float curHP = m_BlackBoard->GetValue<float>("BossCurrHP").value();
		m_BlackBoard->SetValue("BossCurrHP", curHP - 1);

	}

#pragma endregion



	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Update(deltaTime);
	}

	m_UIManager.Update(deltaTime);
}

void InGameUITestScene::Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Render(renderInfo);
	}

	//m_UIManager.Render(uiRenderInfo, uiTextInfo);
}

void InGameUITestScene::SavePlayerInfo()
{
}

void InGameUITestScene::LoadPlayerInfo()
{
}

void InGameUITestScene::RandomSpawnObstacle()
{
}
