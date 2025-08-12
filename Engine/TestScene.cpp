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
	cameraObject->GetComponent<CameraComponent>()->SetZoom((9.0f/16.0f));
	BoxColliderComponent* cameraCol = cameraObject->AddComponent<BoxColliderComponent>();
	cameraCol->Start();
	//cameraCol->SetSize({ 1920, 1080 });
	cameraCol->SetSize({ 2120, 1080 });
	SetMainCamera(cameraObject);

#pragma endregion

#pragma region Background
	{
		auto texture = m_AssetManager.LoadTexture(L"3Chap_2Phase_View", L"../Resource/Character/Boss/Phase_3/3Chap_2Phase_View.png");

		//auto texture = m_AssetManager.LoadTexture(L"3Chap_1Phase_01", L"../Resource/Character/Boss/Phase_1/3Chap_1Phase_01.png");


		auto backobj = std::make_shared<GameObject>(m_EventDispatcher);
		backobj->m_Name = "backgroundtest";
		auto sr = backobj->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());


		auto tr = backobj->GetComponent<TransformComponent>();
		tr->SetPosition({ 960.f, 540.f });
		tr->SetScale({ 0.9f, 0.9f });
		sr->SetOpacity(1.0f);

		tr->SetZOrder(-1);

		AddGameObject(backobj);
	}
#pragma endregion

#pragma region anim_now
	std::vector<std::shared_ptr<GameObject>> m_Anims;
	std::unordered_map<std::string, std::vector<int>> m_AnimIndexMap;

#pragma endregion

#pragma region Boss_IDLE
	//Phase_1
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_Phase_1_Main";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 1700.f, 1320.f });
		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetOpacity(0.f);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_Phase_1_Main", L"../Resource/Character/Boss/Boss_IDLE.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("idle");

		sr->SetPath("../Resource/Boss/Boss_IDLE.json");
		sr->SetTextureKey("Boss_Phase_1_Main");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, {width, height});
		
		AddGameObject(animobj);

		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_Phase_1_Main"].push_back(index);

	}

	//Phase_3
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_3Phase_IDLE_ani";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.f, 1740.f });
		trans->SetScale({ 2.f, 2.f });
		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);


		auto& clips = m_AssetManager.LoadAnimation(L"Boss_3Phase_IDLE_ani", L"../Resource/Character/Boss/Phase_3/Boss_3Phase_IDLE_ani.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("idle");

		sr->SetPath("../Resource/Boss/Phase_3/Boss_3Phase_IDLE_ani.json");
		sr->SetTextureKey("Boss_3Phase_IDLE_ani");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);

		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_3Phase_IDLE_ani"].push_back(index);

	}

#pragma endregion

#pragma region Anim_Pick
	//1페이즈 팔
	for (int i = 0; i < 5; i++)
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_Pick" + std::to_string(i);

		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.f, 800.f });

		trans->SetScale({ 1.0f, 2.0f });

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_Pick", L"../Resource/Character/Boss/Phase_1/Boss_Arm_Pick.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("pick");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		sr->SetPath("../Resource/Boss/Phase_1/Boss_Arm_Pick.json");
		sr->SetTextureKey("Boss_Pick");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::BottomCenter, { width, height });

		AddGameObject(animobj);

		// m_Anims, m_AnimIndexMap는 클래스 멤버라고 가정
		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_Pick"].push_back(index);
	}

	//3페이즈 팔
	for (int i = 0; i < 2; i++)
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_Phase3_Pick" + std::to_string(i);

		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.f, 800.f });

		trans->SetScale({ 1.0f, 2.0f });

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_Phase3_Pick", L"../Resource/Character/Boss/Phase_3/Boss_3Phase_Arm_Pick.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("pick");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		sr->SetPath("../Resource/Boss/Phase_3/Boss_3Phase_Arm_Pick.json");
		sr->SetTextureKey("Boss_Phase3_Pick");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::BottomCenter, { width, height });

		AddGameObject(animobj);

		// m_Anims, m_AnimIndexMap는 클래스 멤버라고 가정
		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_Phase3_Pick"].push_back(index);
	}



#pragma endregion

#pragma region Anim_Smash
	//Phase_1
	for (int i = 0; i < 3; i++)
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_ArmSmash" + std::to_string(i);

		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.f, 800.f });

		trans->SetScale({ 1.8f, 1.0f });

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_ArmSmash", L"../Resource/Character/Boss/Phase_1/Boss_Arm_Smash.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("smash");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		sr->SetPath("../Resource/Boss/Phase_1/Boss_Arm_Smash.json");
		sr->SetTextureKey("Boss_ArmSmash");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::BottomRight, { width, height });

		AddGameObject(animobj);

		// m_Anims, m_AnimIndexMap는 클래스 멤버라고 가정
		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_ArmSmash"].push_back(index);
	}

	//Phase_3
	for (int i = 0; i < 3; i++)
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_3Phase_Arm_Smash" + std::to_string(i);

		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.f, 800.f });

		trans->SetScale({ 1.8f, 1.0f });

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_3Phase_Arm_Smash", L"../Resource/Character/Boss/Phase_1/Boss_3Phase_Arm_Smash.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("smash");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		sr->SetPath("../Resource/Boss/Phase_1/Boss_3Phase_Arm_Smash.json");
		sr->SetTextureKey("Boss_3Phase_Arm_Smash");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::BottomRight, { width, height });

		AddGameObject(animobj);

		// m_Anims, m_AnimIndexMap는 클래스 멤버라고 가정
		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_3Phase_Arm_Smash"].push_back(index);
	}

#pragma endregion

#pragma region Anim_Lazer_CCTV
	//Phase_1
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_Lazer_CCTV";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 1700.f, 1320.f });
		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);


		auto& clips = m_AssetManager.LoadAnimation(L"Boss_Lazer_CCTV", L"../Resource/Character/Boss/Phase_1/Boss_1Phase_Laser_Ani.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("idle");
		anim->SetIsActive(false);

		sr->SetPath("../Resource/Boss/Phase_1/Boss_1Phase_Laser_Ani.json");
		sr->SetTextureKey("Boss_Lazer_CCTV");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);

		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_Lazer_CCTV"].push_back(index);

	}

	//Phase_3
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_3Phase_Laser_CCTV";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.f, 1740.f });
		trans->SetScale({ 2.0f, 2.0f });
		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);


		auto& clips = m_AssetManager.LoadAnimation(L"Boss_3Phase_Laser_Ani", L"../Resource/Character/Boss/Phase_1/Boss_1Phase_Laser_Ani.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("idle");
		anim->SetIsActive(false);

		sr->SetPath("../Resource/Boss/Phase_1/Boss_1Phase_Laser_Ani.json");
		sr->SetTextureKey("Boss_3Phase_Laser_CCTV");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);

		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_3Phase_Laser_CCTV"].push_back(index);

	}

#pragma endregion

#pragma region Anim_Lazer_VFX
	//1페이즈
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_Lazer";

		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 1720.f, 1530.f });

		trans->SetScale({ 1.0f, 2.0f });

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_Lazer", L"../Resource/Character/Boss/Phase_1/Boss_1Phase_Laser_VFX_Ani.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("charge");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		sr->SetPath("../Resource/Boss/Phase_1/Boss_1Phase_Laser_VFX_Ani.json");
		sr->SetTextureKey("Boss_Lazer");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);

		// m_Anims, m_AnimIndexMap는 클래스 멤버라고 가정
		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_Lazer"].push_back(index);
	}

	//3페이즈
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_Lazer_Phase_3";

		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.f, 2030.f });

		trans->SetScale({ 3.0f, 3.0f });

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_3Phase_Laser_VFX_Ani", L"../Resource/Character/Boss/Phase_1/Boss_3Phase_Laser_VFX_Ani.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("charge");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		sr->SetPath("../Resource/Boss/Phase_1/Boss_3Phase_Laser_VFX_Ani.json");
		sr->SetTextureKey("Boss_Lazer_Phase_3");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);

		// m_Anims, m_AnimIndexMap는 클래스 멤버라고 가정
		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_Lazer_Phase_3"].push_back(index);
	}

#pragma endregion

#pragma region Anim_Phase2_Arm
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_Anim_Phase2_Arm";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ -900.f, 240.f });
		trans->SetScale({ 1.0f, 1.0f });

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_Anim_Phase2_Arm", L"../Resource/Character/Boss/Phase_2/Boss_2Phase_Arms_Ani.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("idle");
		anim->SetIsActive(true);
		anim->SetLoop(true);

		sr->SetPath("../Resource/Boss/Phase_2/Boss_2Phase_Arms_Ani.json");
		sr->SetTextureKey("Boss_Anim_Phase2_Arm");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Phase_2_Arm, { width, height });

		AddGameObject(animobj);
		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_Anim_Phase2_Arm"].push_back(index);

		m_Phase_2_Arm = animobj;
	}


#pragma endregion

#pragma region Anim_ArmSwip
	//평상시
	//화면기준 왼팔
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_Anim_Arm_L";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 500.f, 800.f });
		trans->SetScale({ -1.75f, 1.75f });

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_3Phase_Arms_IDLE", L"../Resource/Character/Boss/Phase_3/Boss_3Phase_Arms_IDLE.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("idle");
		anim->SetIsActive(true);
		anim->SetLoop(true);

		sr->SetPath("../Resource/Boss/Phase_3/Boss_3Phase_Arms_IDLE.json");
		sr->SetTextureKey("Boss_Anim_Arm_L");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);
		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_Anim_Arm_L"].push_back(index);

	}

	//화면기준 오른팔
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_Anim_Arm_R";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 1420.f, 800.f });
		trans->SetScale({ 1.75f, 1.75f });

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_3Phase_Arms_IDLE", L"../Resource/Character/Boss/Phase_3/Boss_3Phase_Arms_IDLE.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("idle");
		anim->SetIsActive(true);
		anim->SetLoop(true);

		sr->SetPath("../Resource/Boss/Phase_3/Boss_3Phase_Arms_IDLE.json");
		sr->SetTextureKey("Boss_Anim_Arm_R");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);
		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_Anim_Arm_R"].push_back(index);

	}


	//공격 모션
	//화면기준 왼팔
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_Anim_ArmSwip_L";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 700.f, 800.f });
		trans->SetScale({ -1.5f, 1.5f });
		trans->SetZOrder(200);

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_Anim_ArmSwip", L"../Resource/Character/Boss/Phase_3/Boss_3Phase_ArmSwip.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("swip");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		sr->SetPath("../Resource/Boss/Phase_3/Boss_3Phase_ArmSwip.json");
		sr->SetTextureKey("Boss_Anim_ArmSwip_L");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);
		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_Anim_ArmSwip_L"].push_back(index);

	}

	//화면기준 오른팔
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_Anim_ArmSwip_R";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 1220.f, 1200.f });
		trans->SetScale({ 1.5f, 1.5f });

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_Anim_ArmSwip", L"../Resource/Character/Boss/Phase_3/Boss_3Phase_ArmSwip.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("swip");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		sr->SetPath("../Resource/Boss/Phase_3/Boss_3Phase_ArmSwip.json");
		sr->SetTextureKey("Boss_Anim_ArmSwip_R");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);
		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_Anim_ArmSwip_R"].push_back(index);

	}

#pragma endregion

#pragma region Anim_Dead
	// 본체 사망
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_3Phase_DEAD_Ani";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.f, 1740.f });
		trans->SetScale({ 2.f, 2.f });
		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetOpacity(0.f);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_3Phase_DEAD_Ani", L"../Resource/Character/Boss/Phase_3/Boss_3Phase_DEAD_Ani.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("dead");
		anim->SetLoop(false);
		anim->SetIsActive(false);

		sr->SetPath("../Resource/Boss/Phase_3/Boss_3Phase_DEAD_Ani.json");
		sr->SetTextureKey("Boss_3Phase_DEAD_Ani");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);

		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_3Phase_DEAD_Ani"].push_back(index);

	}

	//화면기준 왼팔
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_3Phase_Arms_Dead_L";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 920.f, 690.f });
		trans->SetScale({ -1.75f, 1.75f });

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetOpacity(0.f);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_3Phase_Arms_Dead_Ani", L"../Resource/Character/Boss/Phase_3/Boss_3Phase_Arms_Dead_Ani.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("dead");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		sr->SetPath("../Resource/Boss/Phase_3/Boss_3Phase_Arms_Dead_Ani.json");
		sr->SetTextureKey("Boss_3Phase_Arms_Dead_L");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);
		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_3Phase_Arms_Dead_L"].push_back(index);

	}

	//화면기준 왼팔
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_3Phase_Arms_Dead_R";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 1000.f, 690.f });
		trans->SetScale({ 1.75f, 1.75f });

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetOpacity(0.f);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_3Phase_Arms_Dead_Ani", L"../Resource/Character/Boss/Phase_3/Boss_3Phase_Arms_Dead_Ani.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("dead");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		sr->SetPath("../Resource/Boss/Phase_3/Boss_3Phase_Arms_Dead_Ani.json");
		sr->SetTextureKey("Boss_3Phase_Arms_Dead_R");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);
		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_3Phase_Arms_Dead_R"].push_back(index);

	}


#pragma endregion

#pragma region Anim_Shot
	//Phase_3
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_3Phase_Shot_Ani";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.f, 1740.f });
		trans->SetScale({ 2.f, 2.f });
		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetOpacity(0.f);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_3Phase_Shot_Ani", L"../Resource/Character/Boss/Phase_3/Boss_3Phase_Shot_Ani.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("shot");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		sr->SetPath("../Resource/Boss/Phase_3/Boss_3Phase_Shot_Ani.json");
		sr->SetTextureKey("Boss_3Phase_Shot_Ani");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);

		m_Anims.push_back(animobj);
		int index = static_cast<int>(m_Anims.size() - 1);
		m_AnimIndexMap["Boss_3Phase_Shot_Ani"].push_back(index);

	}

#pragma endregion


#pragma region telegraph
	m_Telegraphs.reserve(15);

	const int columns = 5;
	const int rows = 3;

	const float startX = 960.f; // 기준 좌표
	const float startY = 0.f;

	const float marginX = 20.0f;
	const float marginY = 20.0f;

	D2D1_SIZE_F tileSize = { 0 };
	auto texture = m_AssetManager.LoadTexture(L"WarningSign", L"../Resource/Character/WarningSign.png");
	if (texture)
		tileSize = texture->GetSize();

	// 기준 인덱스
	const int baseIndex = 7;
	const int baseCol = baseIndex % columns;
	const int baseRow = baseIndex / columns;

	for (int i = 0; i < columns * rows; ++i)
	{
		auto teleobj = std::make_shared<Telegraph>(m_EventDispatcher);
		teleobj->m_Name = "tele" + std::to_string(i);
		auto sr = teleobj->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());

		int col = i % columns;
		int row = i / columns;

		// 7번이 startX, startY에 위치하도록 보정
		float posX = startX + (col - baseCol) * (tileSize.width * 0.7f + marginX);
		float posY = startY + (row - baseRow) * (tileSize.height * 0.7f + marginY);

		std::cout << "posx: " << posX << " posy: " << posY << std::endl;
		auto p_trans = teleobj->GetComponent<TransformComponent>();
		p_trans->SetPosition({ posX, posY });
		p_trans->SetScale({ 0.7f, 0.7f });
		sr->SetOpacity(0.0f);

		AddGameObject(teleobj);
		m_Telegraphs.push_back(teleobj);

		//애니메이션 추가
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Fire_Ground" + std::to_string(i);;
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ posX, posY });
		trans->SetScale({ 2.0f, 2.0f });

		auto a_sr = animobj->AddComponent<SpriteRenderer>();
		a_sr->SetAssetManager(&m_AssetManager);

		auto& clips = m_AssetManager.LoadAnimation(L"Fire_Ground", L"../Resource/Character/Boss/Fire_Ground.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("fire");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		a_sr->SetPath("../Resource/Boss/Fire_Ground.json");
		a_sr->SetTextureKey("Fire_Ground");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		a_sr->SetPivotPreset(SpritePivotPreset::BottomCenter, { width, height });

		AddGameObject(animobj);
		m_Fires.push_back(animobj);
	}



	m_BlackBoard = std::make_unique<BossBlackBoard>(m_ScrollSpeed ,m_Telegraphs, m_Anims, m_Fires, m_AnimIndexMap, m_SoundManager);
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

	//// 카메라 이동량 계산
	//float dx = m_ScrollSpeed * deltaTime;
	//float dy = 0.f;

	//m_TotalXMove += dx;

	//auto camtrans = m_Camera->GetComponent<TransformComponent>();
	//auto curpos = camtrans->GetPosition();
	//camtrans->SetPosition({ curpos.x + 100 * deltaTime, curpos.y });

	//for (auto& telegraph : m_Telegraphs)
	//{
	//	auto tr = telegraph->GetComponent<TransformComponent>();
	//	auto pos = tr->GetPosition();
	//	tr->SetPosition({ pos.x + dx, pos.y + dy });
	//}

	//// 파이어 오브젝트 이동
	//for (auto& fire : m_Fires)
	//{
	//	auto tr = fire->GetComponent<TransformComponent>();
	//	auto pos = tr->GetPosition();
	//	tr->SetPosition({ pos.x + dx, pos.y + dy });
	//}

	//{
	//	auto tr = m_Phase_2_Arm->GetComponent<TransformComponent>();
	//	auto pos = tr->GetPosition();
	//	tr->SetPosition({ pos.x + dx, pos.y + dy });

	//}


	//---------------------

	m_BTElapsedTime += deltaTime;
	m_OneSecondTimer += deltaTime;

	if (m_BTElapsedTime >= 0.016f)
	{
		if (m_BehaviorTree && !m_BlackBoard->GetValue<bool>("IsDead").value())
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
		std::cout << curHP << std::endl;
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
