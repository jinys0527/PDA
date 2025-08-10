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
#include "AnimationClip.h"
#include "GameManager.h"


void TestScene::Initialize()
{
#pragma region camera

	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans3 = cameraObject->GetComponent<TransformComponent>();
	trans3->SetPosition({ 960.0f, 540.f });
	cameraObject->GetComponent<CameraComponent>()->SetZoom(1.0f);
	BoxColliderComponent* cameraCol = cameraObject->AddComponent<BoxColliderComponent>();
	cameraCol->Start();
	//cameraCol->SetSize({ 1920, 1080 });
	cameraCol->SetSize({ 2120, 1080 });
	SetMainCamera(cameraObject);

#pragma endregion

#pragma region Boss_IDLE
	//{
	//	auto bossIdle = std::make_shared<GameObject>(m_EventDispatcher);
	//	bossIdle->m_Name = "BossIdle";
	//	auto trans = bossIdle->GetComponent<TransformComponent>();
	//	trans->SetPosition({ 960, 800 });
	//	auto sr = bossIdle->AddComponent<SpriteRenderer>();
	//	sr->SetAssetManager(&m_AssetManager);
	//	

	//	auto& clips = m_AssetManager.LoadAnimation(L"boss_idle", L"../Resource/Character/Boss/Boss_IDLE.json");
	//	auto anim = bossIdle->AddComponent<AnimationComponent>();
	//	anim->SetAssetManager(&m_AssetManager);

	//	for (const auto& [clipName, clip] : clips)
	//	{
	//		anim->AddClip(clipName, &clip);
	//	}

	//	anim->Play("idle");

	//	sr->SetPath("../Resource/Boss/Boss_IDLE.json");
	//	sr->SetTextureKey("boss");

	//	float width = clips.begin()->second.GetFrames().begin()->Width();
	//	float height = clips.begin()->second.GetFrames().begin()->Height();

	//	sr->SetPivotPreset(SpritePivotPreset::Center, {width, height});
	//	
	//	AddGameObject(bossIdle);
	//}
#pragma endregion

#pragma region Anim_Pick
	//{
	//	auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
	//	animobj->m_Name = "Boss_pick";
	//	auto trans = animobj->GetComponent<TransformComponent>();
	//	trans->SetPosition({ 960, 800 });
	//	auto sr = animobj->AddComponent<SpriteRenderer>();
	//	sr->SetAssetManager(&m_AssetManager);


	//	auto& clips = m_AssetManager.LoadAnimation(L"boss_pick", L"../Resource/Character/Boss/Phase_1/Boss_Arm_Pick.json");
	//	auto anim = animobj->AddComponent<AnimationComponent>();
	//	anim->SetAssetManager(&m_AssetManager);

	//	for (const auto& [clipName, clip] : clips)
	//	{
	//		anim->AddClip(clipName, &clip);
	//	}

	//	anim->Play("pick");

	//	sr->SetPath("../Resource/Boss/Phase_1/Boss_Arm_Pick.json");
	//	sr->SetTextureKey("boss_pick");

	//	float width = clips.begin()->second.GetFrames().begin()->Width();
	//	float height = clips.begin()->second.GetFrames().begin()->Height();

	//	sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

	//	AddGameObject(animobj);
	//}

#pragma endregion

#pragma region Anim_Lazer_VFX
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_Lazer";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 960, 800 });
		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);


		auto& clips = m_AssetManager.LoadAnimation(L"Boss_Lazer", L"../Resource/Character/Boss/Phase_1/Boss_1Phase_Laser_VFX_Ani.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("fire");

		sr->SetPath("../Resource/Boss/Phase_1/Boss_1Phase_Laser_VFX_Ani.json");
		sr->SetTextureKey("Boss_Lazer");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);
	}

#pragma endregion

#pragma region Anim_Arm_Idle
	//{
	//	auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
	//	animobj->m_Name = "Boss_Arm_Idle";
	//	auto trans = animobj->GetComponent<TransformComponent>();
	//	trans->SetPosition({ 960, 800 });
	//	auto sr = animobj->AddComponent<SpriteRenderer>();
	//	sr->SetAssetManager(&m_AssetManager);

	//	auto& clips = m_AssetManager.LoadAnimation(L"Boss_Arm_Idle", L"../Resource/Character/Boss/Phase_1/Boss_1Phase_Arm_Up_IDLE_Ani.json");
	//	auto anim = animobj->AddComponent<AnimationComponent>();
	//	anim->SetAssetManager(&m_AssetManager);

	//	for (const auto& [clipName, clip] : clips)
	//	{
	//		anim->AddClip(clipName, &clip);
	//	}

	//	anim->Play("idle");

	//	sr->SetPath("../Resource/Boss/Phase_1/Boss_1Phase_Arm_Up_IDLE_Ani.json");
	//	sr->SetTextureKey("Boss_Arm_Idle");

	//	float width = clips.begin()->second.GetFrames().begin()->Width();
	//	float height = clips.begin()->second.GetFrames().begin()->Height();

	//	sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

	//	AddGameObject(animobj);
	//}

#pragma endregion

#pragma region Anim_Phase2_Arm
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_Anim_Phase2_Arm";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 960, 800 });
		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_Anim_Phase2_Arm", L"../Resource/Character/Boss/Phase_2/Boss_2Phase_Arms_Ani.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("stretch");

		sr->SetPath("../Resource/Boss/Phase_2/Boss_2Phase_Arms_Ani.json");
		sr->SetTextureKey("Boss_Anim_Phase2_Arm");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);
	}


#pragma endregion


#pragma region anim
	std::vector<std::shared_ptr<GameObject>> m_Anims;

	//보스 스킬에 페이즈 별로 스프라이트 다르게 하도록 Init할 때 코드 추가해야함

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
	m_Telegraphs.reserve(15);

	const int columns = 5;
	const int rows = 3;

	const float startX = 500.0f;
	const float startY = 500.0f;


	const float marginX = 20.0f;
	const float marginY = 20.0f;

	D2D1_SIZE_F tileSize = { 0 };
	auto texture = m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png");

	for (int i = 0; i < columns * rows; ++i)
	{
		auto teleobj = std::make_shared<Telegraph>(m_EventDispatcher);
		teleobj->m_Name = "tele" + std::to_string(i);
		auto sr = teleobj->AddComponent<SpriteRenderer>();
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
 
	m_BlackBoard = std::make_unique<BossBlackBoard>(m_Telegraphs, m_Anims, m_SoundManager);
	m_BehaviorTree = std::make_unique<BossBehaviorTree>(*m_BlackBoard);	m_BehaviorTree->Initialize();
#pragma endregion



	AddGameObject(cameraObject);
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


void TestScene::FixedUpdate()
{
}

void TestScene::Update(float deltaTime)
{
#pragma region BT
	if (time < 3.0f)
	{
		time += deltaTime;
		return; // 3초 지나기 전에는 행동트리 실행 X
	}

	m_BTElapsedTime += deltaTime;
	m_OneSecondTimer += deltaTime;

	if (m_BTElapsedTime >= 0.016f)
	{
		if (m_BehaviorTree)
		{
			m_BehaviorTree->Tick(m_BTElapsedTime);
		}


	m_GameManager->m_scrollSpeed += deltaTime;
	if (m_GameManager->m_scrollSpeed >= 500)
		m_GameManager->m_scrollSpeed = 500;

	Vec2F move = { 0, 0 };
	move.x += m_GameManager->m_scrollSpeed;

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
}

void TestScene::LoadPlayerInfo()
{
}
