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


void TestScene::Initialize()
{

	//#pragma region telegraph
	//	std::vector<std::shared_ptr<Telegraph>> m_Telegraphs;
	//	m_Telegraphs.reserve(12); // Â¸ÃžÂ¸Ã°Â¸Â® ?Ã§Ã?�Ã’Â´Ã�?Â¹Ã¦ÃÃ¶
	//
	//	const int columns = 4;
	//	const int rows = 3;
	//
	//	const float startX = 0.0f;
	//	const float startY = 0.0f;
	//
	//	// Â¿Â©Â¹Ã©(margin) Â¼Â³ÃÂ¤
	//	const float marginX = 20.0f; // Â°Â¡Â·ÃŽ Â°Â£Â°Ã
	//	const float marginY = 20.0f; // Â¼Â¼Â·ÃŽ Â°Â£Â°Ã
	//
	//	D2D1_SIZE_F tileSize = { 0 };
	//
	//	for (int i = 0; i < 12; ++i)
	//	{
	//		auto teleobj = std::make_shared<Telegraph>(m_EventDispatcher);
	//		teleobj->m_Name = "tele" + std::to_string(i);
	//		auto sr = teleobj->AddComponent<SpriteRenderer>();
	//		auto texture = m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png");
	//		sr->SetTexture(texture);
	//		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());
	//
	//		if (i == 0)
	//		{
	//			tileSize = texture->GetSize();
	//		}
	//
	//		int col = i % columns;
	//		int row = i / columns;
	//
	//		// Â°Â£Â°Ã Ã?�Ã·Ã‡Ã�?ÃÃ?�Ã‡Â�?Â°Ã¨Â»Ãª
	//		float posX = startX + col * (tileSize.width + marginX);
	//		float posY = startY + row * (tileSize.height + marginY);
	//
	//		std::cout << "posx: " << posX << " posy: " << posY << std::endl;
	//		teleobj->GetComponent<TransformComponent>()->SetPosition({ posX, posY });
	//		sr->SetOpacity(0.0f);
	//		teleobj->SetZ(row);
	//
	//		AddGameObject(teleobj);
	//		m_Telegraphs.push_back(teleobj);
	//	}
	//
	//
	//
	//
	//#pragma endregion
	//
	//	m_BlackBoard = std::make_unique<BossBlackBoard>(m_Telegraphs);
	//	m_BehaviorTree = std::make_unique<BossBehaviorTree>(*m_BlackBoard);	m_BehaviorTree->Initialize();
	//
	//	{
	//		auto gameObject = std::make_shared<PlayerObject>(m_EventDispatcher);
	//		gameObject->m_Name = "player";
	//		//m_EventDispatcher.AddListener()
	//		auto trans = gameObject->GetComponent<TransformComponent>();
	//		trans->SetPosition({ 960.0f, 540.0f });
	//		auto sr = gameObject->AddComponent<SpriteRenderer>();
	//		sr->SetAssetManager(&m_AssetManager);
	//		auto& clips = m_AssetManager.LoadAnimation(L"boss", L"../Resource/Character/Boss/Boss_Arm_Right_Hit/boss.json");
	//		auto animComp = gameObject->AddComponent<AnimationComponent>();
	//		animComp->SetAssetManager(&m_AssetManager);
	//
	//		gameObject->SetShadowBitmap(m_AssetManager.LoadTexture(L"cat", L"../Resource/cat.png"));
	//
	//		for (const auto& [clipName, clip] : clips)
	//		{
	//			animComp->AddClip(clipName, &clip);
	//		}
	//
	//		//sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());
	//		animComp->Play("attack");
	//		sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
	//		sr->SetTextureKey("boss");
	//		//±×·¡ÇÇÆ¼
	//		auto graffiti = std::make_shared<GraffitiObject>(m_EventDispatcher);
	//		graffiti->m_Name = "graffiti";
	//		auto graffitiTrans = graffiti->GetComponent<TransformComponent>();
	//		graffitiTrans->SetPosition({ 1600,900 });
	//		sr = graffiti->AddComponent<SpriteRenderer>();
	//		sr->SetAssetManager(&m_AssetManager);
	//		auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
	//		sr->SetPath("../Resource/cat.png");
	//		sr->SetTextureKey("cat_texture");
	//		sr->SetTexture(bitmap);
	//		sr->SetPivotPreset(SpritePivotPreset::Center, bitmap->GetSize());
	//		graffiti->GetComponent<GraffitiComponent>()->Start();
	//
	//		AddGameObject(gameObject);
	//		AddGameObject(graffiti);
	//
	//
	//		{
	//			auto obstacle = std::make_shared<Obstacle>(m_EventDispatcher);
	//			obstacle->m_Name = "obstacle";
	//			auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
	//			obstacleTrans->SetPosition({ 1460.0f, 350.0f });
	//			sr = obstacle->AddComponent<SpriteRenderer>();
	//			sr->SetAssetManager(&m_AssetManager);
	//			bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
	//			sr->SetPath("../Resource/cat.png");
	//			sr->SetTextureKey("cat_texture");
	//			sr->SetTexture(bitmap);
	//			sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());
	//
	//			obstacle->SetZ(1);
	//			obstacle->SetSlide(true);
	//
	//			AddGameObject(obstacle);
	//		}
	//
	//		{
	//			auto obstacle = std::make_shared<ItemObject>(m_EventDispatcher);
	//			obstacle->m_Name = "obstacle2";
	//			auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
	//			obstacleTrans->SetPosition({ 1000.0f, 700.0f });
	//			sr = obstacle->AddComponent<SpriteRenderer>();
	//			sr->SetAssetManager(&m_AssetManager);
	//			bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
	//			sr->SetPath("../Resource/cat.png");
	//			sr->SetTextureKey("cat_texture");
	//			sr->SetTexture(bitmap);
	//			sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());
	//
	//			obstacle.get()->SetZ(2);
	//
	//			AddGameObject(obstacle);
	//		}
	//
	//
	//	}
	//
	//
	//	{
	//		auto gameObject = std::make_shared<GameObject>(m_EventDispatcher);
	//		gameObject->m_Name = "test";
	//		auto trans = gameObject->GetComponent<TransformComponent>();
	//		trans->SetPosition({ 300.0f, 300.0f });
	//		auto sr = gameObject->AddComponent<SpriteRenderer>();
	//		sr->SetAssetManager(&m_AssetManager);
	//		auto& clips = m_AssetManager.LoadAnimation(L"boss", L"../Resource/Character/Boss/Boss_Arm_Right_Hit/boss.json");
	//
	//		auto animComp = gameObject->AddComponent<AnimationComponent>();
	//		animComp->SetAssetManager(&m_AssetManager);
	//
	//		for (const auto& [clipName, clip] : clips)
	//		{
	//			animComp->AddClip(clipName, &clip);
	//		}
	//
	//		animComp->Play("attack");
	//
	//		sr->SetPath("../Resource/Boss/Boss_Arm_Right_Hit/boss.json");
	//		sr->SetTextureKey("boss");
	//
	//
	//		AddGameObject(gameObject);
	//	}

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
	//auto backimage1 = m_AssetManager.LoadTexture(L"¹é±×¶ó¿îµå", L"../Resource/Background/¹é±×¶ó¿îµå.png");
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


	{
		auto gameObject = std::make_shared<PlayerObject>(m_EventDispatcher);
		gameObject->m_Name = "player";
		//m_EventDispatcher.AddListener()
		auto trans = gameObject->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.0f, 540.0f });
		auto sr = gameObject->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		//auto& clips1 = m_AssetManager.LoadAnimation(L"Sour_Run_Ani", L"../Resource/Character/Sour/Sour_Run_Ani.json");
		auto animComp = gameObject->AddComponent<AnimationComponent>();
		animComp->SetAssetManager(&m_AssetManager);
		gameObject->SetShadowBitmap(m_AssetManager.LoadTexture(L"cat", L"../Resource/cat.png"));

		//{
		//	auto& clips = m_AssetManager.LoadAnimation(L"boss", L"../Resource/Character/Boss/Boss_Arm_Right_Hit/boss.json");
		//	for (const auto& [clipName, clip] : clips)
		//	{
		//		animComp->AddClip(clipName, &clip);
		//	}
		//}
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
		//{
		//	auto& clips = m_AssetManager.LoadAnimation(L"Sour_Marking_Fail_Ani", L"../Resource/Character/Sour/Sour_Marking_Fail_Ani.json");
		//	for (const auto& [clipName, clip] : clips)
		//	{
		//		animComp->AddClip(clipName, &clip);
		//	}
		//}
		//{
		//	auto& clips = m_AssetManager.LoadAnimation(L"Sour_Marking_Fail_Ani", L"../Resource/Character/Sour/Sour_Marking_Fail_Ani.json");
		//	for (const auto& [clipName, clip] : clips)
		//	{
		//		animComp->AddClip(clipName, &clip);
		//	}
		//}
		//{
		//	auto& clips = m_AssetManager.LoadAnimation(L"Sour_Marking_Fail_Ani", L"../Resource/Character/Sour/Sour_Marking_Fail_Ani.json");
		//	for (const auto& [clipName, clip] : clips)
		//	{
		//		animComp->AddClip(clipName, &clip);
		//	}
		//}
		//sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());
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
			

			effectsr->SetPivotPreset(SpritePivotPreset::HealPivot, {400, 400});

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

	
#pragma region soundUI
	auto soundUI = std::make_shared<SoundUI>(m_SoundManager, m_EventDispatcher);
	soundUI->m_Name = "sound";
	soundUI->SetSlider();
	auto uiText = soundUI->AddComponent<UITextComponent>();
	uiText->SetDWriteFactory(m_Renderer.GetDWriteFactory());
	uiText->SetText(L"UI Ã…Ã˜Â½ÂºÃ†Â® Â¿Â¹Â½Ãƒ");
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


	/*auto uiObj4 = std::make_shared<UIObject>(m_EventDispatcher);
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
	soundUI->GetUI()->SetFill(uiObj4);*/
#pragma endregion

		

	



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


#pragma endregion



	//AddGameObject(gameObject);
  /*sr->SetTexture(bitmap);
	sr2->SetTexture(bitmap);*/
	//AddGameObject(gameObject);
	//AddGameObject(gameObject2);

	m_UIManager.AddUI(soundUI);
	//m_UIManager.AddUI(buttonUI);
	m_UIManager.AddUI(uiObject);
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
				lambdaObstacle->GetComponent<BoxColliderComponent>()->OnTrigger();
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

	if (m_GameObjects.find("Camera") == m_GameObjects.end())
		return;
	PlayerObject* player = (PlayerObject*)(m_GameObjects.find("player")->second.get()); // ??ÂÃ¬Â¨Â·?????Â ???ÂÃ«Â¼Â±Ã¦Â¿?Ã¨Â«?ºÃ«Â¶Â???
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

			if (opponentPos.x > cameraPos.x + 1500)
			{
				continue;
			}
			else if (cameraPos.x - 1500 > opponentPos.x)
			{
				if(!gameObject->second.get()->GetComponent<TransformComponent>()->GetParent())
					removeList.push_back(gameObject->second);
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


	m_GameManager->m_scrollSpeed += deltaTime;
	//if (m_GameManager->m_scrollSpeed >= 1000)
		m_GameManager->m_scrollSpeed = 2000* deltaTime;

	Vec2F move = { 0, 0 };
	move.x += m_GameManager->m_scrollSpeed;
	m_GameObjects.find("Camera")->second->GetComponent<TransformComponent>()->Translate(move);
	m_GameObjects.find("player")->second->GetComponent<TransformComponent>()->Translate(move);


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

void TestScene::Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Render(renderInfo);
	}

	m_UIManager.Render(uiRenderInfo, uiTextInfo);
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
	m_GameManager->m_scrollSpeed = 0;
}

void TestScene::RandomSpawnObstacle()
{
	srand((unsigned)time(NULL));
	rand();
	m_GameObjects;
	{
		auto obstacle = std::make_shared<Obstacle>(m_EventDispatcher);
		obstacle->m_Name = "obstacle";
		auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
		obstacleTrans->SetPosition({ 1460.0f, 350.0f });
		auto sr = obstacle->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
		sr->SetPath("../Resource/cat.png");
		sr->SetTextureKey("cat_texture");
		sr->SetTexture(bitmap);
		sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());

		obstacle->SetZ(1);
		obstacle->SetSlide(true);
	}
	{
		auto obstacle = std::make_shared<ItemObject>(m_EventDispatcher);
		obstacle->m_Name = "item";
		auto obstacleTrans = obstacle->GetComponent<TransformComponent>();
		obstacleTrans->SetPosition({ 1000.0f, 700.0f });
		auto sr = obstacle->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
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
		auto sr = obstacle->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
		sr->SetPath("../Resource/cat.png");
		sr->SetTextureKey("cat_texture");
		sr->SetTexture(bitmap);
		sr->SetPivotPreset(SpritePivotPreset::BottomCenter, bitmap->GetSize());

		obstacle->m_isBullet = true;

		obstacle.get()->SetZ(2);

		AddGameObject(obstacle);
	}
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
		auto lambdaCamera = GetMainCamera();

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
		auto lambdaCamera = GetMainCamera();

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
		auto lambdaCamera = GetMainCamera();

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
