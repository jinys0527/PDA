#include "pch.h"
#include "BossScene.h"
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
#include "ChapterBackgroundManager.h"
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
#include "BossBehaviorTree.h"
#include "BossBlackBoard.h"
#include "GameManager.h"
#include "PlayerEffectComponent.h"
#include "ControlComponent.h"
#include "SceneManager.h"
#include "RectTransformComponent.h"
#include "FixedObstacle_1.h"
#include "FixedObstacle_2.h"
#include "FallingObstacle_Box.h"
#include "FallingObstacle_Flowerpot.h"
#include "SlidingObstacle.h"
#include "Drone.h"
#include <fstream>
#include "ChapterBackgroundManager.h"
#include "LoadingRollerComponent.h"
#include "RollerBackComponent.h"
#include "SwitchingAreaComponent.h"
#include <iostream>


void BossScene::Initialize()
{
#pragma region camera

	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans3 = cameraObject->GetComponent<TransformComponent>();
	trans3->SetPosition({ 960.0f, 540.f });
	BoxColliderComponent* cameraCol = cameraObject->AddComponent<BoxColliderComponent>();
	cameraCol->Start();
	//cameraCol->SetSize({ 1920, 1080 });
	cameraCol->SetSize({ 2120, 1080 });
	SetMainCamera(cameraObject);

#pragma endregion

#pragma region Background

	//3페 구멍 배경
	{
		auto texture = m_AssetManager.LoadTexture(L"3Chap_2Phase_View", L"../Resource/Character/Background/Chapter3/3Chap_2Phase_View.png");

		auto backobj = std::make_shared<GameObject>(m_EventDispatcher);
		backobj->m_Name = "Phase_2_Big_Hole";
		auto sr = backobj->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());


		auto tr = backobj->GetComponent<TransformComponent>();
		tr->SetPosition({ 960.f, 540.f });
		//tr->SetScale({ 0.5f, 0.5f });
		sr->SetOpacity(0.0f);

		tr->SetZOrder(-3);

		AddGameObject(backobj);

		m_Backgrounds[backobj->m_Name] = backobj;
	}

	//3페 구멍 뒷배경
	{
		auto texture = m_AssetManager.LoadTexture(L"3Chap_2Phase_Background02", L"../Resource/Character/Background/Chapter3/3Chap_2Phase_Background02.png");

		auto backobj = std::make_shared<GameObject>(m_EventDispatcher);
		backobj->m_Name = "Phase_3_Hole_Background";
		auto sr = backobj->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());


		auto tr = backobj->GetComponent<TransformComponent>();
		tr->SetPosition({ 960.f, 540.f });
		//tr->SetScale({ 0.5f, 0.5f });
		sr->SetOpacity(0.0f);

		tr->SetZOrder(-5);

		AddGameObject(backobj);

		m_Backgrounds[backobj->m_Name] = backobj;
	}


	//1페 모니터 배경
	{
		auto texture = m_AssetManager.LoadTexture(L"3Chap_1Phase_01", L"../Resource/Character/Boss/Phase_2/3Chap_1Phase_01.png");

		auto backobj = std::make_shared<GameObject>(m_EventDispatcher);
		backobj->m_Name = "Phase_1_Monitor";
		auto sr = backobj->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());


		auto tr = backobj->GetComponent<TransformComponent>();
		tr->SetPosition({ 960.f, 740.f });
		tr->SetScale({ 0.8f, 0.8f });
		sr->SetOpacity(0.0f);

		tr->SetZOrder(-4);

		AddGameObject(backobj);
		m_Backgrounds[backobj->m_Name] = backobj;

	}

	//2페 1번
	{
		auto texture = m_AssetManager.LoadTexture(L"3Chap_2Phase_02", L"../Resource/Character/Boss/Phase_2/3Chap_2Phase_02.png");

		auto backobj = std::make_shared<GameObject>(m_EventDispatcher);
		backobj->m_Name = "Phase_2_Monitor_1";
		auto sr = backobj->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());


		auto tr = backobj->GetComponent<TransformComponent>();
		tr->SetPosition({ 960.f, 740.f });
		tr->SetScale({ 0.8f, 0.8f });
		sr->SetOpacity(0.0f);

		tr->SetZOrder(-4);

		AddGameObject(backobj);
		m_Backgrounds[backobj->m_Name] = backobj;

	}

	//2페 2번
	{
		auto texture = m_AssetManager.LoadTexture(L"3Chap_2Phase_03", L"../Resource/Character/Boss/Phase_2/3Chap_2Phase_03.png");

		auto backobj = std::make_shared<GameObject>(m_EventDispatcher);
		backobj->m_Name = "Phase_2_Monitor_2";
		auto sr = backobj->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());


		auto tr = backobj->GetComponent<TransformComponent>();
		tr->SetPosition({ 960.f, 740.f });
		tr->SetScale({ 0.8f, 0.8f });
		sr->SetOpacity(0.0f);

		tr->SetZOrder(-4);

		AddGameObject(backobj);
		m_Backgrounds[backobj->m_Name] = backobj;

	}

	//2페 3번
	{
		auto texture = m_AssetManager.LoadTexture(L"3Chap_2Phase_04", L"../Resource/Character/Boss/Phase_2/3Chap_2Phase_04.png");

		auto backobj = std::make_shared<GameObject>(m_EventDispatcher);
		backobj->m_Name = "Phase_2_Monitor_3";
		auto sr = backobj->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());


		auto tr = backobj->GetComponent<TransformComponent>();
		tr->SetPosition({ 960.f, 740.f });
		tr->SetScale({ 0.8f, 0.8f });
		sr->SetOpacity(0.0f);

		tr->SetZOrder(-4);

		AddGameObject(backobj);
		m_Backgrounds[backobj->m_Name] = backobj;

	}

	//2페 4번
	{
		auto texture = m_AssetManager.LoadTexture(L"3Chap_2Phase_05", L"../Resource/Character/Boss/Phase_2/3Chap_2Phase_05.png");

		auto backobj = std::make_shared<GameObject>(m_EventDispatcher);
		backobj->m_Name = "Phase_2_Monitor_4";
		auto sr = backobj->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());


		auto tr = backobj->GetComponent<TransformComponent>();
		tr->SetPosition({ 960.f, 740.f });
		tr->SetScale({ 0.8f, 0.8f });
		sr->SetOpacity(0.0f);

		tr->SetZOrder(-4);

		AddGameObject(backobj);
		m_Backgrounds[backobj->m_Name] = backobj;

	}

	//터널 진입 뒷배경 반복
	{
		auto texture = m_AssetManager.LoadTexture(L"3Chap_1Phase_Background_Repeat", L"../Resource/Character/Boss/Phase_1/3Chap_1Phase_Background_Repeat.png");

		auto backobj = std::make_shared<GameObject>(m_EventDispatcher);
		backobj->m_Name = "Phase_1_Background_Repeat";
		auto sr = backobj->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());


		auto tr = backobj->GetComponent<TransformComponent>();
		tr->SetPosition({ 960.f, 540.f });
		tr->SetScale({ 1.f, 1.f });
		sr->SetOpacity(0.0f);

		tr->SetZOrder(-3);

		AddGameObject(backobj);
	}


	//터널 -> 1페 뒷배경1
	{
		auto texture = m_AssetManager.LoadTexture(L"3Chap_1Phase_Background_01", L"../Resource/Character/Boss/Phase_1/3Chap_1Phase_Background_01.png");

		auto backobj = std::make_shared<GameObject>(m_EventDispatcher);
		backobj->m_Name = "Phase_1_Background_1";
		auto sr = backobj->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());


		auto tr = backobj->GetComponent<TransformComponent>();
		tr->SetPosition({ 960.f, 540.f });
		tr->SetScale({ 1.f, 1.f });
		sr->SetOpacity(0.0f);

		tr->SetZOrder(-3);

		AddGameObject(backobj);
	}

	//터널 -> 1페 뒷배경2
	{
		auto texture = m_AssetManager.LoadTexture(L"3Chap_1Phase_Background_02", L"../Resource/Character/Boss/Phase_1/3Chap_1Phase_Background_02.png");

		auto backobj = std::make_shared<GameObject>(m_EventDispatcher);
		backobj->m_Name = "Phase_1_Background_1";
		auto sr = backobj->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());


		auto tr = backobj->GetComponent<TransformComponent>();
		tr->SetPosition({ 960.f, 540.f });
		tr->SetScale({ 1.f, 1.f });
		sr->SetOpacity(0.0f);

		tr->SetZOrder(-3);

		AddGameObject(backobj);
	}

	//1 && 2페 반복
	{
		auto texture = m_AssetManager.LoadTexture(L"3Chap_1Phase_Background_02", L"../Resource/Character/Boss/Phase_1/3Chap_1Phase_Background_02.png");

		auto backobj = std::make_shared<GameObject>(m_EventDispatcher);
		backobj->m_Name = "Phase_1_Background_1";
		auto sr = backobj->AddComponent<SpriteRenderer>();
		sr->SetTexture(texture);
		sr->SetPivotPreset(SpritePivotPreset::Center, texture->GetSize());


		auto tr = backobj->GetComponent<TransformComponent>();
		tr->SetPosition({ 960.f, 540.f });
		tr->SetScale({ 1.f, 1.f });
		sr->SetOpacity(0.0f);

		tr->SetZOrder(-3);

		AddGameObject(backobj);
	}


#pragma endregion

#pragma region anim_now
	std::unordered_map<std::string, std::vector<int>> m_AnimIndexMap;

#pragma endregion

#pragma region Boss_IDLE
	//Phase_1
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_Phase_1_Main";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.f, 1000.f });


		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);

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

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

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
		trans->SetPosition({ 960.f, 1050.f });
		//trans->SetScale({ 2.f, 2.f });
		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetOpacity(0.f);


		auto& clips = m_AssetManager.LoadAnimation(L"Boss_3Phase_IDLE_ani", L"../Resource/Character/Boss/Phase_3/Boss_3Phase_IDLE_ani.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("idle");
		anim->SetIsActive(false);

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

		trans->SetScale({ 0.5f, 1.0f });

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

		trans->SetScale({ 0.5f, 1.0f });

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

		trans->SetScale({ 1.0f, 0.4f });

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

		trans->SetScale({ 1.0f, 0.4f });

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
		trans->SetPosition({ 960.f, 1000.f });

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
		trans->SetPosition({ 960.f, 1050.f });
		//trans->SetScale({ 2.f, 2.f });
		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetOpacity(0.f);

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
		trans->SetPosition({ 1210.f, 1000.f });

		trans->SetScale({ 0.4f, 1.f });

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
		trans->SetPosition({ 960.f, 1200.f });

		trans->SetScale({ 1.5f, 1.5f });

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
		trans->SetScale({ 0.5f, 0.5f });

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
		anim->SetIsActive(false);
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
		trans->SetPosition({ 600.f, 750.f });
		trans->SetScale({ -0.9f, 0.9f });

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetOpacity(0.f);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_3Phase_Arms_IDLE", L"../Resource/Character/Boss/Phase_3/Boss_3Phase_Arms_IDLE.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("idle");
		anim->SetIsActive(false);
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
		trans->SetPosition({ 1320.f, 750.f });
		trans->SetScale({ 0.9f, 0.9f });

		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetOpacity(0.f);

		auto& clips = m_AssetManager.LoadAnimation(L"Boss_3Phase_Arms_IDLE", L"../Resource/Character/Boss/Phase_3/Boss_3Phase_Arms_IDLE.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("idle");
		anim->SetIsActive(false);
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
		trans->SetPosition({ 750.f, 770.f });
		trans->SetScale({ -0.9f, 0.9f });

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
		trans->SetPosition({ 1170.f, 770.f });
		trans->SetScale({ 0.9f, 0.9f });

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
		trans->SetPosition({ 960.f, 1050.f });
		trans->SetScale({ 1.f, 1.f });
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
		trans->SetPosition({ 820.f, 690.f });
		trans->SetScale({ -0.9f, 0.9f });

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

	//화면기준 오른팔
	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Boss_3Phase_Arms_Dead_R";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 1100.f, 690.f });
		trans->SetScale({ 0.9f, 0.9f });

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

#pragma region Effect_Boom

	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Bomb_1";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 560.f, 1740.f });
		trans->SetScale({ 2.f, 2.f });
		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetOpacity(0.f);

		auto& clips = m_AssetManager.LoadAnimation(L"Bomb", L"../Resource/Character/Boss/Phase_3/Bomb.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("bomb");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		sr->SetPath("../Resource/Boss/Phase_3/Bomb.json");
		sr->SetTextureKey("Bomb");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);

		m_Bombs.push_back(animobj);

	}

	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Bomb_2";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.f, 740.f });
		trans->SetScale({ 2.f, 2.f });
		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetOpacity(0.f);

		auto& clips = m_AssetManager.LoadAnimation(L"Bomb", L"../Resource/Character/Boss/Phase_3/Bomb.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("bomb");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		sr->SetPath("../Resource/Boss/Phase_3/Bomb.json");
		sr->SetTextureKey("Bomb");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);

		m_Bombs.push_back(animobj);

	}

	{
		auto animobj = std::make_shared<GameObject>(m_EventDispatcher);
		animobj->m_Name = "Bomb_3";
		auto trans = animobj->GetComponent<TransformComponent>();
		trans->SetPosition({ 1560.f, 740.f });
		trans->SetScale({ 2.f, 2.f });
		auto sr = animobj->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetOpacity(0.f);

		auto& clips = m_AssetManager.LoadAnimation(L"Bomb", L"../Resource/Character/Boss/Phase_3/Bomb.json");
		auto anim = animobj->AddComponent<AnimationComponent>();
		anim->SetAssetManager(&m_AssetManager);

		for (const auto& [clipName, clip] : clips)
		{
			anim->AddClip(clipName, &clip);
		}

		anim->Play("bomb");
		anim->SetIsActive(false);
		anim->SetLoop(false);

		sr->SetPath("../Resource/Boss/Phase_3/Bomb.json");
		sr->SetTextureKey("Bomb");

		float width = clips.begin()->second.GetFrames().begin()->Width();
		float height = clips.begin()->second.GetFrames().begin()->Height();

		sr->SetPivotPreset(SpritePivotPreset::Center, { width, height });

		AddGameObject(animobj);

		m_Bombs.push_back(animobj);

	}


#pragma endregion

#pragma region AttackArea
	auto snipeTexture = m_AssetManager.LoadTexture(L"Snipe", L"../Resource/Character/Boss/Snipe.png");


	{
		auto attackArea = std::make_shared<GraffitiObject>(m_EventDispatcher);
		attackArea->SetName("Snipe1");
		auto sr = attackArea->GetComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetTexture(snipeTexture);
		sr->SetPivotPreset(SpritePivotPreset::Center, snipeTexture->GetSize());
		sr->SetTextureKey("Snipe");

		sr->SetOpacity(0.f);

		attackArea->SetGravittis(&m_AssetManager, 3);

		attackArea->GetComponent<GraffitiComponent>()->Start();

		auto attackAreaTrans = attackArea->GetComponent<TransformComponent>();
		attackAreaTrans->SetPosition({1500.f, 800.f});
		attackAreaTrans->SetZOrder(20);

		AddGameObject(attackArea);
		m_AttackArea.push_back(attackArea);
	}

	{
		auto attackArea = std::make_shared<GraffitiObject>(m_EventDispatcher);
		attackArea->SetName("Snipe3");
		auto sr = attackArea->GetComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetTexture(snipeTexture);
		sr->SetPivotPreset(SpritePivotPreset::Center, snipeTexture->GetSize());
		sr->SetTextureKey("Snipe");

		sr->SetOpacity(0.f);


		attackArea->SetGravittis(&m_AssetManager, 3);

		attackArea->GetComponent<GraffitiComponent>()->Start();

		auto attackAreaTrans = attackArea->GetComponent<TransformComponent>();
		attackAreaTrans->SetPosition({ 960.f, 800.f });
		attackAreaTrans->SetZOrder(20);

		AddGameObject(attackArea);
		m_AttackArea.push_back(attackArea);
	}
#pragma endregion


#pragma region telegraph
	m_Telegraphs.reserve(15);

	const int columns = 5;
	const int rows = 3;

	const float startX = 960.f; // 기준 좌표
	const float startY = 143.f;

	const float marginX = 20.0f;
	const float marginY = 0.0f;

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
		sr->SetPivotPreset(SpritePivotPreset::BottomCenter, texture->GetSize());

		int col = i % columns;
		int row = i / columns;

		teleobj->SetZ(row);

		// 7번이 startX, startY에 위치하도록 보정
		float posX = startX + (col - baseCol) * (tileSize.width * 0.4f + marginX);
		float posY = startY + (row - baseRow) * (tileSize.height * 0.3f + marginY);

		std::cout << "posx: " << posX << " posy: " << posY << std::endl;
		auto p_trans = teleobj->GetComponent<TransformComponent>();
		p_trans->SetPosition({ posX, posY });
		p_trans->SetScale({ 0.4f, 0.3f });
		sr->SetOpacity(0.0f);
		
		teleobj->SetZ(row);

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



#pragma endregion



	m_BlackBoard = std::make_unique<BossBlackBoard>(m_ScrollSpeed, m_AttackArea, m_EventDispatcher ,m_Telegraphs, m_Anims, m_Fires, m_Backgrounds, m_AnimIndexMap, m_SoundManager);
	m_BehaviorTree = std::make_unique<BossBehaviorTree>(*m_BlackBoard);	m_BehaviorTree->Initialize();

	m_BossEventComponent = std::make_unique<BossEventComponent>(m_BlackBoard.get());
	m_BossEventComponent->Start();

#pragma region soundUI

	auto soundUI = std::make_shared<SoundUI>(m_SoundManager, m_EventDispatcher);
	soundUI->SetZOrder(5);
	soundUI->m_Name = "soundUI";
	auto soundUIRect = soundUI->GetComponent<RectTransformComponent>();
	soundUIRect->SetPosition({ -321.0f, -50.0f });
	soundUIRect->SetSize({ 642.0f, 308.0f });
	soundUIRect->SetAnchorPreset(AnchorPrset::FullStretch);
	soundUIRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto soundBGMFrame = std::make_shared<UIObject>(m_EventDispatcher);
	soundBGMFrame->SetZOrder(5);
	auto soundBGMFrameImg = soundBGMFrame->AddComponent<UIImageComponent>();
	soundBGMFrameImg->SetBitmap(m_AssetManager.LoadTexture(L"sound-bar-up-down", "../Resource/UI/Setting/sound-bar-up-down.png"));
	soundBGMFrameImg->SetUV({ 0.0f, 0.0f, 642.0f, 58.0f });
	soundBGMFrameImg->SetPivotPreset(ImagePivotPreset::Center, soundBGMFrameImg->GetTexture()->GetSize());
	auto soundBGMFrameRect = soundBGMFrame->GetComponent<RectTransformComponent>();
	soundBGMFrameRect->SetAnchorPreset(AnchorPrset::FullStretch);
	soundBGMFrameRect->SetPivotPreset(RectTransformPivotPreset::Center);
	soundBGMFrameRect->SetSize({ 642.0f, 58.0f });
	soundBGMFrameRect->SetPosition({ 0.0f, -30.0f });
	soundBGMFrame->SetIsVisible(false);
	soundUI->GetBGM()->SetFrame(soundBGMFrame);

	auto soundBGMFill = std::make_shared<UIObject>(m_EventDispatcher);
	soundBGMFill->SetZOrder(6);
	auto soundBGMFillImg = soundBGMFill->AddComponent<UIImageComponent>();
	soundBGMFillImg->SetBitmap(m_AssetManager.LoadTexture(L"sound-bar-up", "../Resource/UI/Setting/sound-bar-up.png"));
	soundBGMFillImg->SetUV({ 0.0f, 0.0f, 642.0f, 58.0f });
	soundBGMFillImg->SetPivotPreset(ImagePivotPreset::Center, soundBGMFillImg->GetTexture()->GetSize());
	auto soundBGMFillRect = soundBGMFill->GetComponent<RectTransformComponent>();
	soundBGMFillRect->SetAnchorPreset(AnchorPrset::FullStretch);
	soundBGMFillRect->SetPivotPreset(RectTransformPivotPreset::Center);
	soundBGMFillRect->SetSize({ 642.0f, 58.0f });
	soundBGMFillRect->SetPosition({ 0.0f, -30.0f });
	soundBGMFill->SetIsVisible(false);
	soundUI->GetBGM()->SetFill(soundBGMFill);

	auto soundSFXFrame = std::make_shared<UIObject>(m_EventDispatcher);
	soundSFXFrame->SetZOrder(5);
	auto soundSFXFrameImg = soundSFXFrame->AddComponent<UIImageComponent>();
	soundSFXFrameImg->SetBitmap(m_AssetManager.LoadTexture(L"sound-bar-down-down", "../Resource/UI/Setting/sound-bar-down-down.png"));
	soundSFXFrameImg->SetUV({ 0.0f, 0.0f, 642.0f, 58.0f });
	soundSFXFrameImg->SetPivotPreset(ImagePivotPreset::Center, soundSFXFrameImg->GetTexture()->GetSize());
	auto soundSFXFrameRect = soundSFXFrame->GetComponent<RectTransformComponent>();
	soundSFXFrameRect->SetAnchorPreset(AnchorPrset::FullStretch);
	soundSFXFrameRect->SetPivotPreset(RectTransformPivotPreset::Center);
	soundSFXFrameRect->SetSize({ 642.0f, 58.0f });
	soundSFXFrameRect->SetPosition({ 0.0f, 180.0f });
	soundSFXFrame->SetIsVisible(false);
	soundUI->GetSFX()->SetFrame(soundSFXFrame);

	auto soundSFXFill = std::make_shared<UIObject>(m_EventDispatcher);
	soundSFXFill->SetZOrder(6);
	auto soundSFXFillImg = soundSFXFill->AddComponent<UIImageComponent>();
	soundSFXFillImg->SetBitmap(m_AssetManager.LoadTexture(L"sound-bar-down", "../Resource/UI/Setting/sound-bar-down.png"));
	soundSFXFillImg->SetUV({ 0.0f, 0.0f, 642.0f, 58.0f });
	soundSFXFillImg->SetPivotPreset(ImagePivotPreset::Center, soundSFXFillImg->GetTexture()->GetSize());

	auto soundSFXFillRect = soundSFXFill->GetComponent<RectTransformComponent>();
	soundSFXFillRect->SetAnchorPreset(AnchorPrset::FullStretch);
	soundSFXFillRect->SetPivotPreset(RectTransformPivotPreset::Center);
	soundSFXFillRect->SetSize({ 642.0f, 58.0f });
	soundSFXFillRect->SetPosition({ 0.0f, 180.0f });
	soundSFXFill->SetIsVisible(false);
	soundUI->GetSFX()->SetFill(soundSFXFill);

	soundUI->UpdateInteractableFlags();

	m_UIManager.AddUI("BossScene", soundUI);
	m_UIManager.AddUI("BossScene", soundBGMFrame);
	m_UIManager.AddUI("BossScene", soundBGMFill);
	m_UIManager.AddUI("BossScene", soundSFXFrame);
	m_UIManager.AddUI("BossScene", soundSFXFill);


	auto settingBackGround = std::make_shared<UIObject>(m_EventDispatcher);
	settingBackGround->m_Name = "settingBackGround";
	settingBackGround->SetIsFullScreen(true);
	settingBackGround->SetZOrder(4);
	auto settingBackGroundImg = settingBackGround->AddComponent<UIImageComponent>();
	settingBackGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_popup", "../Resource/UI/Setting/setting_popup.png"));
	auto settingBackGroundRect = settingBackGround->GetComponent<RectTransformComponent>();
	settingBackGroundRect->SetAnchorPreset(AnchorPrset::FullStretch);
	settingBackGroundRect->SetPivotPreset(RectTransformPivotPreset::Center);
	settingBackGroundRect->SetSize({ 1920.0f, 1080.0f });
	settingBackGroundRect->SetPosition({ 0.0f, 0.0f });

	auto settingOkButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	settingOkButton->m_Name = "settingOkButton";
	settingOkButton->SetZOrder(5);
	settingOkButton->UpdateInteractableFlags();
	auto settingOkButtonImg = settingOkButton->AddComponent<UIImageComponent>();
	settingOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_ok_button_off", "../Resource/UI/Setting/setting_ok_button_off.png"));
	auto settingOkButtoComp = settingOkButton->GetComponent<UIButtonComponent>();

	settingOkButtoComp->GetFSM().SetOnEnter("Hover", [settingOkButtonImg, this]() { settingOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_ok_button_on", "../Resource/UI/Setting/setting_ok_button_on.png")); });
	settingOkButtoComp->GetFSM().SetOnExit("Hover", [settingOkButtonImg, this]() {	settingOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"setting_ok_button_off", "../Resource/UI/Setting/setting_ok_button_off.png")); });

	std::weak_ptr<UIObject> weaksettingBackGround = settingBackGround;
	std::weak_ptr<ButtonUI> weaksettingOkButton = settingOkButton;
	std::weak_ptr<SoundUI> weakSoundUI = soundUI;

	auto settingOkButtonRect = settingOkButton->GetComponent<RectTransformComponent>();
	settingOkButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	settingOkButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);
	settingOkButtonRect->SetSize({ 428.0f, 107.0f });
	settingOkButtonRect->SetPosition({ 0.0f, 325.0f });

	// 	settingBackGroundRect->AddChild(settingOkButtonRect);
	// 	settingBackGroundRect->AddChild(soundUIRect);

	settingBackGround->SetIsVisible(false);
	settingOkButton->SetIsVisible(false);
	soundUI->SetIsVisible(false);

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

	{
		auto uiObject = std::make_shared<UIObject>(m_EventDispatcher);
		uiObject->m_Name = "grid";
		auto uiRect = uiObject->GetComponent<RectTransformComponent>();
		uiRect->SetPosition({ -700.0f, -510.0f });
		uiRect->SetAnchorPreset(AnchorPrset::FullStretch);
		uiRect->SetPivotPreset(RectTransformPivotPreset::Center);
		auto grid = uiObject->AddComponent<UIGridComponent>();
		grid->SetCellSize({ 53, 44 });
		grid->SetPadding({ 10, 10 });
		grid->SetSpacing({ 5, 5 });
		grid->SetRowColumn(1, 5);

		auto heartUI = std::make_shared<UIObject>(m_EventDispatcher);
		auto heart = heartUI->AddComponent<UIImageComponent>();
		heart->SetBitmap(m_AssetManager.LoadTexture(L"heart1", "../Resource/UI/InGame/ingame_hp_icon_1.png"));
		heart->SetUV({ 0.0f, 0.0f, 53.0f, 44.0f });
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
		heart->SetBitmap(m_AssetManager.LoadTexture(L"heart2", "../Resource/UI/InGame/ingame_hp_icon_2.png"));
		heart->SetUV({ 0.0f, 0.0f, 53.0f, 44.0f });
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
		heart->SetBitmap(m_AssetManager.LoadTexture(L"heart3", "../Resource/UI/InGame/ingame_hp_icon_3.png"));
		heart->SetUV({ 0.0f, 0.0f, 53.0f, 44.0f });
		heart->SetPivotPreset(ImagePivotPreset::Center, heart->GetTexture()->GetSize());
		rect6 = heartUI3->GetComponent<RectTransformComponent>();
		rect6->SetAnchorPreset(AnchorPrset::FullStretch);
		rect6->SetPivotPreset(RectTransformPivotPreset::Center);
		grid->AddItem(heartUI3);
		heartUIComp = heartUI3->AddComponent<HeartUIComponent>();
		heartUIComp->Start();
		heartUIComp->SetHpLoc(2);

		auto heartUI4 = std::make_shared<UIObject>(m_EventDispatcher);
		heart = heartUI4->AddComponent<UIImageComponent>();
		heart->SetBitmap(m_AssetManager.LoadTexture(L"heart1", "../Resource/UI/InGame/ingame_hp_icon_1.png"));
		heart->SetUV({ 0.0f, 0.0f, 53.0f, 44.0f });
		heart->SetPivotPreset(ImagePivotPreset::Center, heart->GetTexture()->GetSize());
		rect6 = heartUI4->GetComponent<RectTransformComponent>();
		rect6->SetAnchorPreset(AnchorPrset::FullStretch);
		rect6->SetPivotPreset(RectTransformPivotPreset::Center);
		grid->AddItem(heartUI4);
		heartUIComp = heartUI4->AddComponent<HeartUIComponent>();
		heartUIComp->Start();
		heartUIComp->SetHpLoc(3);

		auto heartUI5 = std::make_shared<UIObject>(m_EventDispatcher);
		heart = heartUI5->AddComponent<UIImageComponent>();
		heart->SetBitmap(m_AssetManager.LoadTexture(L"heart2", "../Resource/UI/InGame/ingame_hp_icon_2.png"));
		heart->SetUV({ 0.0f, 0.0f, 53.0f, 44.0f });
		heart->SetPivotPreset(ImagePivotPreset::Center, heart->GetTexture()->GetSize());
		rect6 = heartUI5->GetComponent<RectTransformComponent>();
		rect6->SetAnchorPreset(AnchorPrset::FullStretch);
		rect6->SetPivotPreset(RectTransformPivotPreset::Center);
		grid->AddItem(heartUI5);
		heartUIComp = heartUI5->AddComponent<HeartUIComponent>();
		heartUIComp->Start();
		heartUIComp->SetHpLoc(4);


		grid->UpdateLayout();

		m_UIManager.AddUI("BossScene", uiObject);

		auto chargeUI = std::make_shared<UIObject>(m_EventDispatcher);
		chargeUI->m_Name = "chargeUI";
		auto chargeUIRect = chargeUI->GetComponent<RectTransformComponent>();
		chargeUIRect->SetPosition({ -925.0f, -330.0f });
		chargeUIRect->SetSize({ 112.0f, 58.0f });
		chargeUIRect->SetAnchorPreset(AnchorPrset::FullStretch);
		chargeUIRect->SetPivotPreset(RectTransformPivotPreset::Center);
		auto chargeImage = chargeUI->AddComponent<UIImageComponent>();
		chargeImage->SetBitmap(m_AssetManager.LoadTexture(L"charge", "../Resource/UI/InGame/ingame_chargeshot_icon.png"));
		chargeImage->SetPivotPreset(ImagePivotPreset::Center, chargeImage->GetTexture()->GetSize());

		m_UIManager.AddUI("BossScene", chargeUI);

		auto chargeCountUI = std::make_shared<UIObject>(m_EventDispatcher);
		chargeCountUI->m_Name = "chargeCountUI";
		auto chargeCountUIRect = chargeCountUI->GetComponent<RectTransformComponent>();
		chargeCountUIRect->SetAnchorPreset(AnchorPrset::FullStretch);
		chargeCountUIRect->SetPivotPreset(RectTransformPivotPreset::Center);
		chargeCountUIRect->SetPosition({ -1080.0f, -597.5f });
		chargeCountUIRect->SetSize({ 600.f, 600.f });
		auto chargeCountUIGrid = chargeCountUI->AddComponent<UIGridComponent>();
		chargeCountUIGrid->SetCellSize({ 50, 50 });
		chargeCountUIGrid->SetPadding({ 0, 0 });
		chargeCountUIGrid->SetSpacing({ -10, 0 });
		chargeCountUIGrid->SetRowColumn(1, 2);

		auto countUI = std::make_shared<UIObject>(m_EventDispatcher);
		auto countUIImg = countUI->AddComponent<UIImageComponent>();
		countUIImg->SetBitmap(m_AssetManager.LoadTexture(L"bullet_count_0", "../Resource/UI/InGame/bullet_count_0.png"));
		countUIImg->SetUV({ 0.0f, 0.0f, 50.0f, 50.0f });
		countUIImg->SetPivotPreset(ImagePivotPreset::Center, countUIImg->GetTexture()->GetSize());
		auto countUIRect = countUI->GetComponent<RectTransformComponent>();
		countUIRect->SetAnchorPreset(AnchorPrset::FullStretch);
		countUIRect->SetPivotPreset(RectTransformPivotPreset::Center);
		chargeCountUIGrid->AddItem(countUI);

		auto countUI2 = std::make_shared<UIObject>(m_EventDispatcher);
		auto countUI2Img = countUI2->AddComponent<UIImageComponent>();
		countUI2Img->SetBitmap(m_AssetManager.LoadTexture(L"bullet_count_0", "../Resource/UI/InGame/bullet_count_0.png"));
		countUI2Img->SetUV({ 0.0f, 0.0f, 50.0f, 50.0f });
		countUI2Img->SetPivotPreset(ImagePivotPreset::Center, countUI2Img->GetTexture()->GetSize());
		auto countUI2Rect = countUI2->GetComponent<RectTransformComponent>();
		countUI2Rect->SetAnchorPreset(AnchorPrset::FullStretch);
		countUI2Rect->SetPivotPreset(RectTransformPivotPreset::Center);
		chargeCountUIGrid->AddItem(countUI2);

		chargeCountUIGrid->UpdateLayout();

		auto bulletUIComp = chargeCountUI->AddComponent<BulletUIComponent>();
		bulletUIComp->Start();
		bulletUIComp->SetNumbers(&m_AssetManager);


		m_UIManager.AddUI("BossScene", chargeCountUI);

		m_UIManager.AddUI("BossScene", uiObject);

		auto portraitUI = std::make_shared<UIObject>(m_EventDispatcher);
		portraitUI->m_Name = "portraitUI";
		auto portraitUIRect = portraitUI->GetComponent<RectTransformComponent>();
		portraitUIRect->SetPosition({ -935.0f, -540.0f });
		portraitUIRect->SetSize({ 303.0f, 210.0f });
		portraitUIRect->SetAnchorPreset(AnchorPrset::FullStretch);
		portraitUIRect->SetPivotPreset(RectTransformPivotPreset::Center);
		auto portraitImage = portraitUI->AddComponent<UIImageComponent>();
		portraitImage->SetBitmap(m_AssetManager.LoadTexture(L"portrait", "../Resource/UI/InGame/ingame_portrait.png"));
		portraitImage->SetPivotPreset(ImagePivotPreset::Center, portraitImage->GetTexture()->GetSize());

		m_UIManager.AddUI("BossScene", portraitUI);
	}

#pragma endregion

#pragma region Exit
	auto exitBackGround = std::make_shared<UIObject>(m_EventDispatcher);
	exitBackGround->m_Name = "exitBackGround";
	exitBackGround->SetIsFullScreen(true);
	exitBackGround->SetZOrder(4);
	auto exitBackGroundImg = exitBackGround->AddComponent<UIImageComponent>();
	exitBackGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_popup", "../Resource/UI/Exit/exitconfirm_popup.png"));
	exitBackGroundImg->SetUV({ 1920.0f, 1080.0f });
	auto exitBackGroundRect = exitBackGround->GetComponent<RectTransformComponent>();
	exitBackGroundRect->SetPosition({ -960.0f, -540.0f });
	exitBackGroundRect->SetSize({ 1920.0f, 1080.0f });
	exitBackGroundRect->SetAnchorPreset(AnchorPrset::FullStretch);
	exitBackGroundRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto exitOkButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	exitOkButton->m_Name = "exitOkButton";
	exitOkButton->SetZOrder(5);
	exitOkButton->UpdateInteractableFlags();
	auto exitOkButtonImg = exitOkButton->AddComponent<UIImageComponent>();
	exitOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_ok_button_off", "../Resource/UI/Exit/exitconfirm_ok_button_off.png"));
	exitOkButtonImg->SetUV({ 405.0f, 102.0f });
	auto exitOkButtonComp = exitOkButton->GetComponent<UIButtonComponent>();
	exitOkButtonComp->GetFSM().SetOnEnter("Hover", [exitOkButtonImg, this]() { exitOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_ok_button_on", "../Resource/UI/Exit/exitconfirm_ok_button_on.png")); });
	exitOkButtonComp->GetFSM().SetOnExit("Hover", [exitOkButtonImg, this]() { exitOkButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_ok_button_off", "../Resource/UI/Exit/exitconfirm_ok_button_off.png")); });
	exitOkButtonComp->GetFSM().SetOnEnter("Click", [this]() {
		if (m_SceneManager)
		{
			m_SceneManager->RequestQuit();
		}
		});
	auto exitOkButtonRect = exitOkButton->GetComponent<RectTransformComponent>();
	exitOkButtonRect->SetPosition({ -430.0f, 210.0f });
	exitOkButtonRect->SetSize({ 405.0f, 102.0f });
	exitOkButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	exitOkButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto exitNoButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	exitNoButton->m_Name = "exitNoButton";
	exitNoButton->SetZOrder(5);
	exitNoButton->UpdateInteractableFlags();
	auto exitNoButtonImg = exitNoButton->AddComponent<UIImageComponent>();
	exitNoButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_no_button_off", "../Resource/UI/Exit/exitconfirm_no_button_off.png"));
	exitNoButtonImg->SetUV({ 405.0f, 102.0f });
	auto exitNoButtonComp = exitNoButton->GetComponent<UIButtonComponent>();
	exitNoButtonComp->GetFSM().SetOnEnter("Hover", [exitNoButtonImg, this]() { exitNoButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_no_button_on", "../Resource/UI/Exit/exitconfirm_no_button_on.png")); });
	exitNoButtonComp->GetFSM().SetOnExit("Hover", [exitNoButtonImg, this]() { exitNoButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"exitconfirm_no_button_off", "../Resource/UI/Exit/exitconfirm_no_button_off.png")); });

	std::weak_ptr<UIObject> weakexitBackGround = exitBackGround;
	std::weak_ptr<ButtonUI> weakexitOkButton = exitOkButton;
	std::weak_ptr<ButtonUI> weakexitNoButton = exitNoButton;


	auto exitNoButtonRect = exitNoButton->GetComponent<RectTransformComponent>();
	exitNoButtonRect->SetPosition({ 0.0f, 210.0f });
	exitNoButtonRect->SetSize({ 405.0f, 102.0f });
	exitNoButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	exitNoButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	// 	exitBackGroundRect->AddChild(exitOkButtonRect);
	// 	exitBackGroundRect->AddChild(exitNoButtonRect);

	exitBackGround->SetIsVisible(false);
	exitOkButton->SetIsVisible(false);
	exitNoButton->SetIsVisible(false);

	m_UIManager.AddUI("BossScene", exitBackGround);
	m_UIManager.AddUI("BossScene", exitOkButton);
	m_UIManager.AddUI("BossScene", exitNoButton);
#pragma endregion


#pragma region menuBox
	auto menuBox = std::make_shared<UIObject>(m_EventDispatcher);
	menuBox->m_Name = "menuBox";
	menuBox->SetIsFullScreen(true);
	menuBox->SetZOrder(2);
	auto menuBoxImg = menuBox->AddComponent<UIImageComponent>();
	menuBoxImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_popup", "../Resource/UI/Pause/pause_popup.png"));


	auto menuBoxRect = menuBox->GetComponent<RectTransformComponent>();
	menuBoxRect->SetSize({ 1920.0f, 1080.0f });
	menuBoxRect->SetPosition({ 0.0f, 0.0f });
	menuBoxRect->SetAnchorPreset(AnchorPrset::FullStretch);
	menuBoxRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto startButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	startButton->m_Name = "startButton";
	startButton->SetZOrder(3);
	startButton->UpdateInteractableFlags();
	auto startButtonImg = startButton->AddComponent<UIImageComponent>();
	startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_resume_button_off", "../Resource/UI/Pause/pause_resume_button_off.png"));
	startButtonImg->SetUV({ 650.0f, 161.0f });
	auto startButtonComp = startButton->GetComponent<UIButtonComponent>();
	startButtonComp->GetFSM().SetOnEnter("Hover", [startButtonImg, this]() { startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_resume_button_on", "../Resource/UI/Pause/pause_resume_button_on.png")); });
	startButtonComp->GetFSM().SetOnExit("Hover", [startButtonImg, this]() {	startButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_resume_button_off", "../Resource/UI/Pause/pause_resume_button_off.png")); });


	auto startButtonRect = startButton->GetComponent<RectTransformComponent>();
	auto test = startButtonRect->GetOwner();
	auto ui = dynamic_cast<UIObject*>(test);
	startButtonRect->SetPosition({ -346.0f, -200.0f });
	startButtonRect->SetSize({ 692.0f, 68.0f });
	startButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	startButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);


	auto settingButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	settingButton->m_Name = "settingButton";
	settingButton->SetZOrder(3);
	settingButton->UpdateInteractableFlags();
	auto settingButtonImg = settingButton->AddComponent<UIImageComponent>();
	settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_setting_button_off", "../Resource/UI/Pause/pause_setting_button_off.png"));
	auto settingButtonComp = settingButton->GetComponent<UIButtonComponent>();
	settingButtonComp->GetFSM().SetOnEnter("Hover", [settingButtonImg, this]() {settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_setting_button_on", "../Resource/UI/Pause/pause_setting_button_on.png")); });
	settingButtonComp->GetFSM().SetOnExit("Hover", [settingButtonImg, this]() {settingButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_setting_button_off", "../Resource/UI/Pause/pause_setting_button_off.png")); });

	auto settingButtonRect = settingButton->GetComponent<RectTransformComponent>();
	settingButtonRect->SetPosition({ -346.0f, -100.0f });
	settingButtonRect->SetSize({ 692.0f, 68.0f });
	settingButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	settingButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto mainButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	mainButton->m_Name = "mainButton";
	mainButton->SetZOrder(3);
	mainButton->UpdateInteractableFlags();
	auto mainButtonImg = mainButton->AddComponent<UIImageComponent>();
	mainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_main_button_off", "../Resource/UI/Pause/pause_main_button_off.png"));
	auto mainButtonComp = mainButton->GetComponent<UIButtonComponent>();
	mainButtonComp->GetFSM().SetOnEnter("Hover", [mainButtonImg, this]() {mainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_main_button_on", "../Resource/UI/Pause/pause_main_button_on.png")); });
	mainButtonComp->GetFSM().SetOnExit("Hover", [mainButtonImg, this]() {mainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_main_button_off", "../Resource/UI/Pause/pause_main_button_off.png")); });

	auto mainButtonRect = mainButton->GetComponent<RectTransformComponent>();
	mainButtonRect->SetPosition({ -346.0f, 0.0f });
	mainButtonRect->SetSize({ 692.0f, 68.0f });
	mainButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	mainButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto retryButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	retryButton->m_Name = "retryButton";
	retryButton->SetZOrder(3);
	retryButton->UpdateInteractableFlags();
	auto retryButtonImg = retryButton->AddComponent<UIImageComponent>();
	retryButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_retry_button_off", "../Resource/UI/Pause/pause_retry_button_off.png"));
	auto retryButtonComp = retryButton->GetComponent<UIButtonComponent>();
	retryButtonComp->GetFSM().SetOnEnter("Hover", [retryButtonImg, this]() {retryButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_retry_button_on", "../Resource/UI/Pause/pause_retry_button_on.png")); });
	retryButtonComp->GetFSM().SetOnExit("Hover", [retryButtonImg, this]() {retryButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_retry_button_off", "../Resource/UI/Pause/pause_retry_button_off.png")); });

	auto retryButtonRect = retryButton->GetComponent<RectTransformComponent>();
	retryButtonRect->SetPosition({ -346.0f, 100.0f });
	retryButtonRect->SetSize({ 692.0f, 68.0f });
	retryButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	retryButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto exitButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	exitButton->m_Name = "exitButton";
	exitButton->SetZOrder(3);
	exitButton->UpdateInteractableFlags();
	auto exitButtonImg = exitButton->AddComponent<UIImageComponent>();
	exitButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_exit_button_off", "../Resource/UI/Pause/pause_exit_button_off.png"));
	auto exitButtonComp = exitButton->GetComponent<UIButtonComponent>();
	exitButtonComp->GetFSM().SetOnEnter("Hover", [exitButtonImg, this]() {exitButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_exit_button_on", "../Resource/UI/Pause/pause_exit_button_on.png")); });
	exitButtonComp->GetFSM().SetOnExit("Hover", [exitButtonImg, this]() {exitButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"pause_exit_button_off", "../Resource/UI/Pause/pause_exit_button_off.png")); });

	auto exitButtonRect = exitButton->GetComponent<RectTransformComponent>();
	exitButtonRect->SetPosition({ -346.0f, 200.0f });
	exitButtonRect->SetSize({ 692.0f, 68.0f });
	exitButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	exitButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	auto escButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	escButton->m_Name = "escButton";
	escButton->SetZOrder(1);
	escButton->UpdateInteractableFlags();
	auto escButtonImg = escButton->AddComponent<UIImageComponent>();
	escButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"ingame_setting_icon", "../Resource/UI/InGame/ingame_setting_icon.png"));
	auto escButtonComp = escButton->GetComponent<UIButtonComponent>();

	auto escButtonRect = escButton->GetComponent<RectTransformComponent>();
	escButtonRect->SetPosition({ 875.0, -525.0f });
	escButtonRect->SetSize({ 72.0f, 71.0f });
	escButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	escButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	menuBox->SetIsVisible(false);
	startButton->SetIsVisible(false);
	settingButton->SetIsVisible(false);
	mainButton->SetIsVisible(false);
	retryButton->SetIsVisible(false);
	exitButton->SetIsVisible(false);
	escButton->SetIsVisible(true);

#pragma endregion

#pragma region gameover

	auto gameoverBox = std::make_shared<UIObject>(m_EventDispatcher);
	gameoverBox->m_Name = "gameoverBox";
	gameoverBox->SetIsFullScreen(true);
	gameoverBox->SetZOrder(3);
	auto gameoverBoxImg = gameoverBox->AddComponent<UIImageComponent>();
	gameoverBoxImg->SetBitmap(m_AssetManager.LoadTexture(L"gameover_popup", "../Resource/UI/GameOver/gameover_popup.png"));


	auto gameoverBoxRect = gameoverBox->GetComponent<RectTransformComponent>();
	gameoverBoxRect->SetSize({ 1920.0f, 1080.0f });
	gameoverBoxRect->SetPosition({ 0.0f, 0.0f });
	gameoverBoxRect->SetAnchorPreset(AnchorPrset::FullStretch);
	gameoverBoxRect->SetPivotPreset(RectTransformPivotPreset::Center);

	gameoverBox->SetIsVisible(false);

	m_UIManager.AddUI("BossScene", gameoverBox);

	auto gameoverRetryButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	gameoverRetryButton->m_Name = "gameoverRetryButton";
	gameoverRetryButton->SetZOrder(4);
	gameoverRetryButton->UpdateInteractableFlags();
	auto gameoverRetryButtonImg = gameoverRetryButton->AddComponent<UIImageComponent>();
	gameoverRetryButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"gameover_retry_button_off", "../Resource/UI/GameOver/gameover_retry_button_off.png"));
	auto gameoverRetryButtonComp = gameoverRetryButton->GetComponent<UIButtonComponent>();
	gameoverRetryButtonComp->GetFSM().SetOnEnter("Hover", [gameoverRetryButtonImg, this]() {gameoverRetryButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"gameover_retry_button_on", "../Resource/UI/GameOver/gameover_retry_button_on.png")); });
	gameoverRetryButtonComp->GetFSM().SetOnExit("Hover", [gameoverRetryButtonImg, this]() {gameoverRetryButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"gameover_retry_button_off", "../Resource/UI/GameOver/gameover_retry_button_off.png")); });

	auto gameoverRetryButtonRect = gameoverRetryButton->GetComponent<RectTransformComponent>();
	gameoverRetryButtonRect->SetPosition({ 370.0f, 130.0f });
	gameoverRetryButtonRect->SetSize({ 460.0f, 116.0f });
	gameoverRetryButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	gameoverRetryButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	gameoverRetryButton->SetIsVisible(false);

	m_UIManager.AddUI("BossScene", gameoverRetryButton);

	auto gameoverMainButton = std::make_shared<ButtonUI>(m_EventDispatcher);
	gameoverMainButton->m_Name = "gameoverMainButton";
	gameoverMainButton->SetZOrder(4);
	gameoverMainButton->UpdateInteractableFlags();
	auto gameoverMainButtonImg = gameoverMainButton->AddComponent<UIImageComponent>();
	gameoverMainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"gameover_main_button_off", "../Resource/UI/GameOver/gameover_main_button_off.png"));
	auto gameoverMainButtonComp = gameoverMainButton->GetComponent<UIButtonComponent>();
	gameoverMainButtonComp->GetFSM().SetOnEnter("Hover", [gameoverMainButtonImg, this]() {gameoverMainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"gameover_main_button_on", "../Resource/UI/GameOver/gameover_main_button_on.png")); });
	gameoverMainButtonComp->GetFSM().SetOnExit("Hover", [gameoverMainButtonImg, this]() {gameoverMainButtonImg->SetBitmap(m_AssetManager.LoadTexture(L"gameover_main_button_off", "../Resource/UI/GameOver/gameover_main_button_off.png")); });

	auto gameoverMainButtonRect = gameoverMainButton->GetComponent<RectTransformComponent>();
	gameoverMainButtonRect->SetPosition({ 370.0f, 270.0f });
	gameoverMainButtonRect->SetSize({ 460.0f, 116.0f });
	gameoverMainButtonRect->SetAnchorPreset(AnchorPrset::FullStretch);
	gameoverMainButtonRect->SetPivotPreset(RectTransformPivotPreset::Center);

	gameoverMainButton->SetIsVisible(false);

	m_UIManager.AddUI("BossScene", gameoverMainButton);

#pragma endregion

#pragma region loading


	auto loadingBackGround = std::make_shared<UIObject>(m_EventDispatcher);
	loadingBackGround->m_Name = "Roller1";
	//exitBackGround->SetIsFullScreen(true);
	loadingBackGround->SetZOrder(6);
	auto loadingBackGroundImg = loadingBackGround->AddComponent<UIImageComponent>();
	loadingBackGroundImg->SetBitmap(m_AssetManager.LoadTexture(L"Roller", "../Resource/UI/Loading/Roller.png"));
	loadingBackGroundImg->SetUV({ 893.0f, 1932.0f });
	auto loadingBackGroundRect = loadingBackGround->GetComponent<RectTransformComponent>();
	loadingBackGroundRect->SetPosition({ -1220.0f, -550.0f });
	loadingBackGroundRect->SetSize({ 1000.0f, 2000.0f });
	loadingBackGroundRect->SetAnchorPreset(AnchorPrset::FullStretch);
	loadingBackGroundRect->SetPivotPreset(RectTransformPivotPreset::Center);

	loadingBackGround->SetIsVisible(true);
	auto loadingComp = loadingBackGround->AddComponent<LoadingRollerComponent>();
	loadingComp->SetIndex(0);
	loadingComp->SetScenePtr(this);



	auto loadingBackGround2 = std::make_shared<UIObject>(m_EventDispatcher);
	loadingBackGround2->m_Name = "Roller2";
	//exitBackGround->SetIsFullScreen(true);
	loadingBackGround2->SetZOrder(7);
	auto loadingBackGroundImg2 = loadingBackGround2->AddComponent<UIImageComponent>();
	loadingBackGroundImg2->SetBitmap(m_AssetManager.LoadTexture(L"Roller", "../Resource/UI/Loading/Roller.png"));
	loadingBackGroundImg2->SetUV({ 893.0f, 1932.0f });
	auto loadingBackGroundRect2 = loadingBackGround2->GetComponent<RectTransformComponent>();
	loadingBackGroundRect2->SetPosition({ -500.0f, -550.0f });
	loadingBackGroundRect2->SetSize({ 1000.0f, 2000.0f });
	loadingBackGroundRect2->SetAnchorPreset(AnchorPrset::FullStretch);
	loadingBackGroundRect2->SetPivotPreset(RectTransformPivotPreset::Center);

	loadingBackGround2->SetIsVisible(true);

	auto loadingComp2 = loadingBackGround2->AddComponent<LoadingRollerComponent>();
	loadingComp2->SetIndex(1);
	loadingComp2->SetScenePtr(this);



	auto loadingBackGround3 = std::make_shared<UIObject>(m_EventDispatcher);
	loadingBackGround3->m_Name = "Roller3";
	//exitBackGround->SetIsFullScreen(true);
	loadingBackGround3->SetZOrder(8);
	auto loadingBackGroundImg3 = loadingBackGround3->AddComponent<UIImageComponent>();
	loadingBackGroundImg3->SetBitmap(m_AssetManager.LoadTexture(L"Roller", "../Resource/UI/Loading/Roller.png"));
	loadingBackGroundImg3->SetUV({ 893.0f, 1932.0f });
	auto loadingBackGroundRect3 = loadingBackGround3->GetComponent<RectTransformComponent>();
	loadingBackGroundRect3->SetPosition({ 219.9f, -550.0f });
	loadingBackGroundRect3->SetSize({ 1000.0f, 2000.0f });
	loadingBackGroundRect3->SetAnchorPreset(AnchorPrset::FullStretch);
	loadingBackGroundRect3->SetPivotPreset(RectTransformPivotPreset::Center);

	loadingBackGround3->SetIsVisible(true);

	auto loadingComp3 = loadingBackGround3->AddComponent<LoadingRollerComponent>();
	loadingComp3->SetIndex(2);
	loadingComp3->SetScenePtr(this);
	loadingComp3->SetFunc([this]
		{
			this->m_SceneManager->ChangeScene();
		});

	auto loadingBackGround4 = std::make_shared<UIObject>(m_EventDispatcher);
	loadingBackGround4->m_Name = "Roller4";
	loadingBackGround4->SetZOrder(9);
	//loadingBackGround4->SetIsFullScreen(true);
	auto loadingBackGroundImg4 = loadingBackGround4->AddComponent<UIImageComponent>();
	loadingBackGroundImg4->SetBitmap(m_AssetManager.LoadTexture(L"LODING", "../Resource/UI/Loading/LODING.png"));
	loadingBackGroundImg4->SetUV({ 1920.0f, 1080.0f });
	auto loadingBackGroundRect4 = loadingBackGround4->GetComponent<RectTransformComponent>();
	loadingBackGroundRect4->SetPosition({ -1920.0f, -540.0f });
	loadingBackGroundRect4->SetSize({ 3000.0f, 1080.0f });
	loadingBackGroundRect4->SetAnchorPreset(AnchorPrset::FullStretch);
	loadingBackGroundRect4->SetPivotPreset(RectTransformPivotPreset::Center);

	loadingBackGround4->SetIsVisible(true);

	auto loadingComp4 = loadingBackGround4->AddComponent<RollerBackComponent>();
	loadingComp4->SetScenePtr(this);


	m_EventDispatcher.AddListener(EventType::OnLoadedScene, loadingComp);
	m_EventDispatcher.AddListener(EventType::OnLoadedScene, loadingComp2);
	m_EventDispatcher.AddListener(EventType::OnLoadedScene, loadingComp3);
	m_EventDispatcher.AddListener(EventType::OnLoadedScene, loadingComp4);

	m_UIManager.AddUI("BossScene", loadingBackGround);
	m_UIManager.AddUI("BossScene", loadingBackGround2);
	m_UIManager.AddUI("BossScene", loadingBackGround3);
	m_UIManager.AddUI("BossScene", loadingBackGround4);
	m_SceneManager->SetChangeScene("TitleScene");


#pragma endregion

#pragma region swichingarea

	auto switchingArea = std::make_shared<UIObject>(m_EventDispatcher);
	switchingArea->m_Name = "switchingArea";
	switchingArea->SetIsFullScreen(false);
	switchingArea->SetZOrder(-1);
	auto switchingAreaImg = switchingArea->AddComponent<UIImageComponent>();
	switchingAreaImg->SetBitmap(m_AssetManager.LoadTexture(L"Switch_screen", "../Resource/UI/Loading/Switch_screen.png"));


	auto switchingAreaRect = switchingArea->GetComponent<RectTransformComponent>();
	switchingAreaRect->SetSize({ 2000.0f, 1080.0f });
	switchingAreaRect->SetPosition({ -2000.0f, 0.0f });
	switchingAreaRect->SetAnchorPreset(AnchorPrset::FullStretch);
	switchingAreaRect->SetPivotPreset(RectTransformPivotPreset::Center);

	switchingArea->SetIsVisible(true);
	switchingArea->AddComponent<SwitchingAreaComponent>();
	//switchingArea->AddComponent<SwitchingAreaComponent>()->Start(1);

	m_UIManager.AddUI("BossScene", switchingArea);

	auto switchingArea2 = std::make_shared<UIObject>(m_EventDispatcher);
	switchingArea2->m_Name = "switchingArea2";
	switchingArea2->SetIsFullScreen(false);
	switchingArea2->SetZOrder(-1);
	auto switchingAreaImg2 = switchingArea2->AddComponent<UIImageComponent>();
	switchingAreaImg2->SetBitmap(m_AssetManager.LoadTexture(L"Switch_screen_2", "../Resource/UI/Loading/Switch_screen_2.png"));


	auto switchingAreaRect2 = switchingArea2->GetComponent<RectTransformComponent>();
	switchingAreaRect2->SetSize({ 2000.0f, 1080.0f });
	switchingAreaRect2->SetPosition({ -2000.0f, 0.0f });
	switchingAreaRect2->SetAnchorPreset(AnchorPrset::FullStretch);
	switchingAreaRect2->SetPivotPreset(RectTransformPivotPreset::Center);

	switchingArea2->SetIsVisible(true);
	switchingArea2->AddComponent<SwitchingAreaComponent>();
	//switchingArea2->AddComponent<SwitchingAreaComponent>()->Start(0);

	m_UIManager.AddUI("BossScene", switchingArea2);

#pragma endregion
	//AddGameObject(gameObject);
  /*sr->SetTexture(bitmap);
	sr2->SetTexture(bitmap);*/
	//AddGameObject(gameObject);
	//AddGameObject(gameObject2);
	m_UIManager.AddUI("BossScene", settingBackGround);
	m_UIManager.AddUI("BossScene", settingOkButton);
	m_UIManager.AddUI("BossScene", menuBox);
	m_UIManager.AddUI("BossScene", startButton);
	m_UIManager.AddUI("BossScene", settingButton);
	m_UIManager.AddUI("BossScene", mainButton);
	m_UIManager.AddUI("BossScene", retryButton);
	m_UIManager.AddUI("BossScene", exitButton);
	m_UIManager.AddUI("BossScene", escButton);

	std::weak_ptr<UIObject> weakGameOverBox = gameoverBox;
	std::weak_ptr<ButtonUI> weakGameOverRetryButton = gameoverRetryButton;
	std::weak_ptr<ButtonUI> weakGameOverMainButton = gameoverMainButton;

	// 약한 참조 만들기
	std::weak_ptr<UIObject> weakMenuBox = menuBox;
	std::weak_ptr<ButtonUI> weakStartButton = startButton;
	std::weak_ptr<ButtonUI> weakSettingButton = settingButton;
	std::weak_ptr<ButtonUI> weakMainButton = mainButton;
	std::weak_ptr<ButtonUI> weakRetryButton = retryButton;
	std::weak_ptr<ButtonUI> weakExitButton = exitButton;

	gameoverRetryButtonComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, weakGameOverBox, weakGameOverMainButton, weakGameOverRetryButton, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(false);
		if (auto bg = weakGameOverBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakGameOverMainButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakGameOverRetryButton.lock()) btn->SetIsVisible(false);

		LoadPlayerInfo();

		m_UIManager.RefreshUIListForCurrentScene();
		});

	gameoverMainButtonComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, loadingComp, loadingComp2, loadingComp3, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(false);

		m_SceneManager->SetChangeScene("TitleScene");

		loadingComp->Start();
		loadingComp2->Start();
		loadingComp3->Start();

		m_UIManager.RefreshUIListForCurrentScene();
		});

	startButtonComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(false);

		m_UIManager.RefreshUIListForCurrentScene();
		});

	// SettingButton 클릭 시
	settingButtonComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, weaksettingBackGround, weaksettingOkButton, weakSoundUI, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(false);

		if (auto bg = weaksettingBackGround.lock()) bg->SetIsVisible(true);
		if (auto btn = weaksettingOkButton.lock()) btn->SetIsVisible(true);
		if (auto soundUI = weakSoundUI.lock()) soundUI->SetIsVisible(true);

		m_UIManager.RefreshUIListForCurrentScene();
		});

	//Setting창 Ok
	settingOkButtoComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, weaksettingBackGround, weaksettingOkButton, weakSoundUI, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(true);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(true);

		if (auto bg = weaksettingBackGround.lock()) bg->SetIsVisible(false);
		if (auto btn = weaksettingOkButton.lock()) btn->SetIsVisible(false);
		if (auto soundUI = weakSoundUI.lock()) soundUI->SetIsVisible(false);

		m_UIManager.RefreshUIListForCurrentScene();
		});

	//ExitNo
	exitNoButtonComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, weakexitBackGround, weakexitOkButton, weakexitNoButton, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(true);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(true);

		if (auto bg = weakexitBackGround.lock()) bg->SetIsVisible(false);
		if (auto btn = weakexitOkButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakexitNoButton.lock()) btn->SetIsVisible(false);
		m_UIManager.RefreshUIListForCurrentScene();
		});

	mainButtonComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, loadingComp, loadingComp2, loadingComp3, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(false);

		m_SceneManager->SetChangeScene("TitleScene");

		loadingComp->Start();
		loadingComp2->Start();
		loadingComp3->Start();

		m_UIManager.RefreshUIListForCurrentScene();
		});

	retryButtonComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(false);

		LoadPlayerInfo();

		m_UIManager.RefreshUIListForCurrentScene();
		});

	exitButtonComp->GetFSM().SetOnEnter("Click", [weakMenuBox, weakStartButton, weakSettingButton, weakMainButton, weakRetryButton, weakExitButton, weakexitBackGround, weakexitOkButton, weakexitNoButton, this]() {
		if (auto bg = weakMenuBox.lock()) bg->SetIsVisible(false);
		if (auto btn = weakStartButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakSettingButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakMainButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakRetryButton.lock()) btn->SetIsVisible(false);
		if (auto btn = weakExitButton.lock()) btn->SetIsVisible(false);

		if (auto bg = weakexitBackGround.lock()) bg->SetIsVisible(true);
		if (auto btn = weakexitOkButton.lock()) btn->SetIsVisible(true);
		if (auto btn = weakexitNoButton.lock()) btn->SetIsVisible(true);

		m_UIManager.RefreshUIListForCurrentScene();
		});

	auto controlObject = std::make_shared<GameObject>(m_EventDispatcher);
	controlObject->SetName("Control");
	auto controlComp = controlObject->AddComponent<ControlComponent>();
	controlComp->Start();

	std::weak_ptr<UIObject> weakmenuBox = menuBox;
	std::weak_ptr<ButtonUI> weakstartButton = startButton;
	std::weak_ptr<ButtonUI> weaksettingButton = settingButton;
	std::weak_ptr<ButtonUI> weakmainButton = mainButton;
	std::weak_ptr<ButtonUI> weakretryButton = retryButton;
	std::weak_ptr<ButtonUI> weakexitButton = exitButton;

	escButtonComp->GetFSM().SetOnEnter("Click", [weakmenuBox, weakstartButton, weaksettingButton, weakmainButton, weakretryButton, weakexitButton, weaksettingBackGround, weaksettingOkButton, weakSoundUI, weakexitBackGround, weakexitOkButton, weakexitNoButton, this]() {
		auto snd = weakSoundUI.lock();
		auto eb = weakexitBackGround.lock();
		if (snd && eb)
		{
			if (snd->IsVisible() || eb->IsVisible())
			{
				if (auto bg = weakmenuBox.lock())	bg->SetIsVisible(true);
				if (auto btn = weakstartButton.lock())	btn->SetIsVisible(true);
				if (auto btn = weaksettingButton.lock())	btn->SetIsVisible(true);
				if (auto btn = weakmainButton.lock())	btn->SetIsVisible(true);
				if (auto btn = weakretryButton.lock())	btn->SetIsVisible(true);
				if (auto btn = weakexitButton.lock())	btn->SetIsVisible(true);
			}
			else
			{
				if (auto bg = weakmenuBox.lock())
				{
					bg->SetIsVisible(!bg->IsVisible());
				}
				if (auto btn = weakstartButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
				if (auto btn = weaksettingButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
				if (auto btn = weakmainButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
				if (auto btn = weakretryButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
				if (auto btn = weakexitButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
			}
			if (snd->IsVisible())
			{
				if (auto bg = weaksettingBackGround.lock()) bg->SetIsVisible(false);
				if (auto btn = weaksettingOkButton.lock()) btn->SetIsVisible(false);
				snd->SetIsVisible(false);
			}
			if (eb->IsVisible())
			{
				eb->SetIsVisible(false);
				if (auto btn = weakexitOkButton.lock()) btn->SetIsVisible(false);

				if (auto btn = weakexitNoButton.lock()) btn->SetIsVisible(false);

			}
		}

		m_UIManager.RefreshUIListForCurrentScene();
		});

	controlComp->RegisterKeyDownCallback(VK_ESCAPE, [weakmenuBox, weakstartButton, weaksettingButton, weakmainButton, weakretryButton, weakexitButton, weaksettingBackGround, weaksettingOkButton, weakSoundUI, weakexitBackGround, weakexitOkButton, weakexitNoButton, weakGameOverBox, this]() {
		if (auto bg = weakGameOverBox.lock())
		{
			if (bg->IsVisible())
				return;
		}
		auto snd = weakSoundUI.lock();
		auto eb = weakexitBackGround.lock();
		if (snd && eb)
		{
			if (snd->IsVisible() || eb->IsVisible())
			{
				if (auto bg = weakmenuBox.lock())	bg->SetIsVisible(true);
				if (auto btn = weakstartButton.lock())	btn->SetIsVisible(true);
				if (auto btn = weaksettingButton.lock())	btn->SetIsVisible(true);
				if (auto btn = weakmainButton.lock())	btn->SetIsVisible(true);
				if (auto btn = weakretryButton.lock())	btn->SetIsVisible(true);
				if (auto btn = weakexitButton.lock())	btn->SetIsVisible(true);
			}
			else
			{
				if (auto bg = weakmenuBox.lock())
				{
					bg->SetIsVisible(!bg->IsVisible());
				}
				if (auto btn = weakstartButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
				if (auto btn = weaksettingButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
				if (auto btn = weakmainButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
				if (auto btn = weakretryButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
				if (auto btn = weakexitButton.lock())
				{
					btn->SetIsVisible(!btn->IsVisible());
				}
			}
			if (snd->IsVisible())
			{
				if (auto bg = weaksettingBackGround.lock()) bg->SetIsVisible(false);
				if (auto btn = weaksettingOkButton.lock()) btn->SetIsVisible(false);
				snd->SetIsVisible(false);
			}
			if (eb->IsVisible())
			{
				eb->SetIsVisible(false);
				if (auto btn = weakexitOkButton.lock()) btn->SetIsVisible(false);

				if (auto btn = weakexitNoButton.lock()) btn->SetIsVisible(false);

			}
		}

		m_UIManager.RefreshUIListForCurrentScene();
		});

	//controlComp->RegisterKeyDownCallback(VK_ESCAPE, [weakexitBackGround, weakexitOkButton, weakexitNoButton, this]() {
	//	if (auto bg = weakexitBackGround.lock()) bg->SetIsVisible(true);
	//	if (auto btn = weakexitOkButton.lock()) btn->SetIsVisible(true);
	//	if (auto btn = weakexitNoButton.lock()) btn->SetIsVisible(true);
	//	m_UIManager.RefreshUIListForCurrentScene();
	//	});

	controlComp->RegisterAnyKeyCallback([loadingComp, loadingComp2, loadingComp3, loadingBackGround4, this]() {

		//loadingComp->Start();
		//loadingComp2->Start();
		//loadingComp3->Start();

		//loadingBackGround4->SetIsVisible(!loadingBackGround4->IsVisible());

		m_UIManager.RefreshUIListForCurrentScene();
		});

	AddGameObject(controlObject);

	//m_UIManager.AddUI(buttonUI);

	m_UIManager.RefreshUIListForCurrentScene();

	{
		auto gameObject = std::make_shared<PlayerObject>(m_EventDispatcher);
		gameObject->m_Name = "player";
		auto trans = gameObject->GetComponent<TransformComponent>();
		trans->SetPosition({ 960.0f, 540.0f });
		auto sr = gameObject->AddComponent<SpriteRenderer>();
		sr->SetAssetManager(&m_AssetManager);
		sr->SetTexture(m_AssetManager.LoadTexture(L"shadow", L"../Resource/Character/Sour/Shadow.png"));
		auto animComp = gameObject->AddComponent<AnimationComponent>();
		animComp->SetAssetManager(&m_AssetManager);
		gameObject->SetShadowBitmap(m_AssetManager.LoadTexture(L"shadow", L"../Resource/Character/Sour/Shadow.png"));
		auto playerbox = gameObject->AddComponent<BoxColliderComponent>();
		playerbox->Start();
		playerbox->SetSize({ 150, 50 });


		std::weak_ptr<PlayerObject> weakplayer = gameObject;

		gameObject->GetFSM().SetOnUpdate("Death", [weakplayer, weakGameOverBox, weakGameOverMainButton, weakGameOverRetryButton, this](float dt)
			{
				if (auto player = weakplayer.lock())
				{
					if (player->GetComponent<AnimationComponent>()->IsAnimationFinished())
					{
						if (auto bg = weakGameOverBox.lock())
							bg->SetIsVisible(true);
						if (auto btn = weakGameOverMainButton.lock())
							btn->SetIsVisible(true);
						if (auto btn = weakGameOverRetryButton.lock())
							btn->SetIsVisible(true);
					}
				}
			});

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

			effectsr->SetTexture(m_AssetManager.LoadTexture(L"Shadow", L"../Resource/Character/Sour/Shadow.png"));
			effectsr->SetPath("../Resource/Character/Sour/Sour_Heal_Ani.json");
			effectsr->SetTextureKey("Sour_Heal_Ani");


			effectsr->SetPivotPreset(SpritePivotPreset::HealPivot, { 400, 400 });

			auto effectComp = effect->AddComponent<PlayerEffectComponent>();
			effectComp->Start();

			AddGameObject(effect);
		}
	}

	AddGameObject(cameraObject);


	{
		/*auto tile = std::make_shared<GameObject>(m_EventDispatcher);
		auto tileSr = tile->AddComponent<SpriteRenderer>();
		tileSr->SetTexture(m_AssetManager.LoadTexture(L"4a", "../Resource/Character/Boss/Phase_1/4a.png"));
		tileSr->SetPivotPreset(SpritePivotPreset::BottomCenter, tileSr->GetTexture()->GetSize());
		auto tileTrans = tile->GetComponent<TransformComponent>();
		tileTrans->SetPosition({ 960.0f, 0.0f });
		tileTrans->SetZOrder(-2);
		AddGameObject(tile);*/

		m_ChapterBackgroundManager = std::make_shared<ChapterBackgroundManager>(&m_AssetManager, m_EventDispatcher);
		m_ChapterBackgroundManager->m_Name = "bg";
		m_ChapterBackgroundManager->LoadBackgroundSet(3);
		
		for (auto& bg : m_ChapterBackgroundManager->GetAllBackgrounds())
		{
			AddGameObject(bg);
		}
		AddGameObject(m_ChapterBackgroundManager);
	}

}

void BossScene::Finalize()
{

}

void BossScene::Enter()
{
	auto player = dynamic_cast<PlayerObject*>(m_GameObjects.find("player")->second.get());
	player->SetScene(true);

	auto escController = m_GameObjects.find("Control")->second->GetComponent<ControlComponent>();
	escController->Enter();

	m_EventDispatcher.Dispatch(EventType::OnLoadedScene, this);

	LoadPlayerInfo();
}

void BossScene::Leave()
{
	auto escController = m_GameObjects.find("Control")->second->GetComponent<ControlComponent>();
	escController->Leave();
	auto player = dynamic_cast<PlayerObject*>(m_GameObjects.find("player")->second.get());
	player->SetScene(false);
}

void ObjectCollisionLeave2(EventDispatcher& eventDispatcher, BoxColliderComponent* enemy, BoxColliderComponent* player)
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

void BossScene::FixedUpdate()
{
	if (m_GameObjects.find("player") == m_GameObjects.end())
		return;
	if (m_GameObjects.find("Camera") == m_GameObjects.end())
		return;
	PlayerObject* player = (PlayerObject*)(m_GameObjects.find("player")->second.get());
	GameObject* cameraObject = GetMainCamera();

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

			if (opponentPos.x > cameraPos.x + 1500 || cameraPos.x - 1500 > opponentPos.x)
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


			if (enemy = dynamic_cast<Obstacle*>(gameObject->second.get()))
				opponentZ = enemy->GetZ();
			else if (ally = dynamic_cast<ItemObject*>(gameObject->second.get()))
				opponentZ = ally->GetZ();
			else
				continue;
			if (opponentZ - 0.5f > playerZ || opponentZ + 0.5f < playerZ)
			{
				ObjectCollisionLeave2(m_EventDispatcher, opponentBox, playerBox);
				continue;
			}

			if (enemy)
			{
				if (enemy->GetSlide() && player->GetSlide())
				{
					ObjectCollisionLeave2(m_EventDispatcher, opponentBox, playerBox);
					continue;
				}
			}

			if (!opponentBox->GetIsActive())
			{
				ObjectCollisionLeave2(m_EventDispatcher, opponentBox, playerBox);
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
					opponentPos.y += 10000;
					ally->GetComponent<TransformComponent>()->SetPosition(opponentPos);
					//RemoveGameObject(gameObject->second);
					//m_GameObjects.erase(gameObject->first);
					//gameObject--;
				}
				continue;
			}

			ObjectCollisionLeave2(m_EventDispatcher, opponentBox, playerBox);
		}
	}
}

void BossScene::Update(float deltaTime)
{
#pragma region BT

	if (time < 3.0f)
	{
		time += deltaTime;

		return; // 3초 지나기 전에는 행동트리 실행 X
	}

	if (m_BlackBoard->GetValue<int>("CurrPhase").value() == 1)
	{
		m_ChapterBackgroundManager->LoadBackgroundSet(4);
		for (auto& bg : m_ChapterBackgroundManager->GetAllBackgrounds())
		{
			AddGameObject(bg);
		}
	}

	if (m_BlackBoard->GetValue<int>("CurrPhase").value() == 2)
	{
		m_ScrollSpeed = 800.f;
	}

	if (m_BlackBoard->GetValue<int>("CurrPhase").value() == 3)
	{
		m_ScrollSpeed = 0.f;
	}

	m_BlackBoard->SetValue("ScrollSpeed", m_ScrollSpeed);

	// 카메라 이동량 계산
	float dx = m_ScrollSpeed * deltaTime;
	float dy = 0.f;

	m_TotalXMove += dx;

	auto camtrans = m_Camera->GetComponent<TransformComponent>();
	auto curpos = camtrans->GetPosition();
	camtrans->SetPosition({ curpos.x + dx , curpos.y });



	for (auto& telegraph : m_Telegraphs)
	{
		auto tr = telegraph->GetComponent<TransformComponent>();
		auto pos = tr->GetPosition();
		tr->SetPosition({ pos.x + dx, pos.y + dy });
	}

	for (auto& obj : m_AttackArea)
	{
		auto tr = obj->GetComponent<TransformComponent>();
		auto pos = tr->GetPosition();
		tr->SetPosition({ pos.x + dx, pos.y + dy });
	}


	for (auto& anim : m_Anims)
	{
		if (anim->m_Name == "Boss_Anim_Phase2_Arm") continue;
		auto tr = anim->GetComponent<TransformComponent>();
		auto pos = tr->GetPosition();
		tr->SetPosition({ pos.x + dx, pos.y + dy });

	}

	for (auto& bomb : m_Bombs)
	{
		auto tr = bomb->GetComponent<TransformComponent>();
		auto pos = tr->GetPosition();
		tr->SetPosition({ pos.x + dx, pos.y + dy });

	}

	for (auto& background : m_Backgrounds)
	{
		auto tr = background.second->GetComponent<TransformComponent>();
		auto pos = tr->GetPosition();
		tr->SetPosition({ pos.x + dx, pos.y + dy });

	}

	// 파이어 오브젝트 이동
	for (auto& fire : m_Fires)
	{
		auto tr = fire->GetComponent<TransformComponent>();
		auto pos = tr->GetPosition();
		tr->SetPosition({ pos.x + dx, pos.y + dy });
	}

	{
		auto tr = m_Phase_2_Arm->GetComponent<TransformComponent>();
		auto pos = tr->GetPosition();
		tr->SetPosition({ pos.x + dx, pos.y + dy });

	}

	{
		auto player = dynamic_cast<PlayerObject*>(m_GameObjects.find("player")->second.get());
		auto tr = player->GetComponent<TransformComponent>();
		auto pos = tr->GetPosition();
		tr->SetPosition({ pos.x + dx, pos.y + dy });

	}

	if (m_ChapterBackgroundManager)
	{
		m_ChapterBackgroundManager->Update(deltaTime, GetMainCamera());
	}

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
		m_BlackBoard->SetValue("BossCurrHP", curHP);
		std::cout << curHP << std::endl;
	}

	if (m_BlackBoard->GetValue<int>("CurrPhase").value() == 3)
	{
		for (auto& obj : m_Bombs)
		{
			obj->GetComponent<SpriteRenderer>()->SetOpacity(1.0f);
			obj->GetComponent<AnimationComponent>()->SetIsActive(true);
			m_SoundManager.SFX_Shot(L"boss_laser_explosion");
		}
	}

#pragma endregion

	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Update(deltaTime);
	}

	auto cameraPos = m_GameObjects.find("Camera")->second->GetComponent<TransformComponent>()->GetPosition();
	auto playerPos = m_GameObjects.find("player")->second->GetComponent<TransformComponent>()->GetPosition();

	if (playerPos.x > cameraPos.x + 900)
		playerPos.x = cameraPos.x + 900;
	if (playerPos.x < cameraPos.x - 900)
		playerPos.x = cameraPos.x - 900;

	m_GameObjects.find("player")->second->GetComponent<TransformComponent>()->SetPosition(playerPos);

	m_UIManager.Update(deltaTime);
}

void BossScene::Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Render(renderInfo);
	}

	m_UIManager.Render(uiRenderInfo, uiTextInfo);
}

void BossScene::SavePlayerInfo()
{
}

void BossScene::LoadPlayerInfo()
{
}

void BossScene::OnLoadComplete()
{
	m_IsLoaded = true;
}
