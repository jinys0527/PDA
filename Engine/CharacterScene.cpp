#include "pch.h"
#include "CharacterScene.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "CameraObject.h"
#include "CameraComponent.h"
#include "AnimationComponent.h"
#include "AnimationController.h"

void CharacterScene::Initialize()
{
	/*auto sourRun = std::make_shared<GameObject>(m_EventDispatcher);
	sourRun->m_Name = "sourRun";
	auto trans = sourRun->GetComponent<TransformComponent>();
	trans->SetPosition({ -960.0f, 1080.0f });
	auto sr = sourRun->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto& clips1 = m_AssetManager.LoadAnimation(L"Sour_Run_Ani", L"../Resource/Character/Sour/Sour_Run_Ani.json");

	auto animComp = sourRun->AddComponent<AnimationComponent>();
	animComp->SetAssetManager(&m_AssetManager);

	for (const auto& [clipName, clip] : clips1)
	{
		animComp->AddClip(clipName, &clip);
	}

	animComp->Play("run");

	sr->SetPath("../Resource/Character/Sour/Sour_Run_Ani.json");
	sr->SetTextureKey("Sour_Run_Ani");


	AddGameObject(sourRun);


	auto sourSlide = std::make_shared<GameObject>(m_EventDispatcher);
	sourSlide->m_Name = "sourSlide";
	trans = sourSlide->GetComponent<TransformComponent>();
	trans->SetPosition({ -560.0f, 1080.0f });
	sr = sourSlide->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto& clips2 = m_AssetManager.LoadAnimation(L"Sour_Slide_Ani", L"../Resource/Character/Sour/Sour_Slide_Ani.json");

	animComp = sourSlide->AddComponent<AnimationComponent>();
	animComp->SetAssetManager(&m_AssetManager);

	for (const auto& [clipName, clip] : clips2)
	{
		animComp->AddClip(clipName, &clip);
	}

	animComp->Play("slide");

	sr->SetPath("../Resource/Character/Sour/Sour_Slide_Ani.json");
	sr->SetTextureKey("Sour_Slide_Ani");


	AddGameObject(sourSlide);


	auto sourAttack = std::make_shared<GameObject>(m_EventDispatcher);
	sourAttack->m_Name = "sourAttack";
	trans = sourAttack->GetComponent<TransformComponent>();
	trans->SetPosition({ -160.0f, 1080.0f });
	sr = sourAttack->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto& clips3 = m_AssetManager.LoadAnimation(L"Sour_Attack_Ani", L"../Resource/Character/Sour/Sour_Attack_Ani.json");

	animComp = sourAttack->AddComponent<AnimationComponent>();
	animComp->SetAssetManager(&m_AssetManager);

	for (const auto& [clipName, clip] : clips3)
	{
		animComp->AddClip(clipName, &clip);
	}

	animComp->Play("attack");

	sr->SetPath("../Resource/Character/Sour/Sour_Attack_Ani.json");
	sr->SetTextureKey("Sour_Attack_Ani");


	AddGameObject(sourAttack);


	auto sourChargeShot = std::make_shared<GameObject>(m_EventDispatcher);
	sourChargeShot->m_Name = "sourChargeShot";
	trans = sourChargeShot->GetComponent<TransformComponent>();
	trans->SetPosition({ 240.0f, 1080.0f });
	sr = sourChargeShot->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto& clips4 = m_AssetManager.LoadAnimation(L"Sour_Charge_Shot_Ani", L"../Resource/Character/Sour/Sour_Charge_Shot_Ani.json");

	animComp = sourChargeShot->AddComponent<AnimationComponent>();
	animComp->SetAssetManager(&m_AssetManager);

	for (const auto& [clipName, clip] : clips4)
	{
		animComp->AddClip(clipName, &clip);
	}

	animComp->Play("chargeshot");

	sr->SetPath("../Resource/Character/Sour/Sour_Charge_Shot_Ani.json");
	sr->SetTextureKey("Sour_Charge_Shot_Ani");


	AddGameObject(sourChargeShot);



	auto sourDead = std::make_shared<GameObject>(m_EventDispatcher);
	sourDead->m_Name = "sourDead";
	trans = sourDead->GetComponent<TransformComponent>();
	trans->SetPosition({ 640.0f, 1080.0f });
	sr = sourDead->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto& clips5 = m_AssetManager.LoadAnimation(L"Sour_Dead_Ani", L"../Resource/Character/Sour/Sour_Dead_Ani.json");

	animComp = sourDead->AddComponent<AnimationComponent>();
	animComp->SetAssetManager(&m_AssetManager);

	for (const auto& [clipName, clip] : clips5)
	{
		animComp->AddClip(clipName, &clip);
	}

	animComp->Play("dead");

	sr->SetPath("../Resource/Character/Sour/Sour_Dead_Ani.json");
	sr->SetTextureKey("Sour_Dead_Ani");


	AddGameObject(sourDead);


	auto sourHeal = std::make_shared<GameObject>(m_EventDispatcher);
	sourHeal->m_Name = "sourHeal";
	trans = sourHeal->GetComponent<TransformComponent>();
	trans->SetPosition({ -960.0f, 680.0f });
	sr = sourHeal->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto& clips6 = m_AssetManager.LoadAnimation(L"Sour_Heal_Ani", L"../Resource/Character/Sour/Sour_Heal_Ani.json");

	animComp = sourHeal->AddComponent<AnimationComponent>();
	animComp->SetAssetManager(&m_AssetManager);

	for (const auto& [clipName, clip] : clips6)
	{
		animComp->AddClip(clipName, &clip);
	}

	animComp->Play("heal");

	sr->SetPath("../Resource/Character/Sour/Sour_Heal_Ani.json");
	sr->SetTextureKey("Sour_Heal_Ani");


	AddGameObject(sourHeal);


	auto sourHitted = std::make_shared<GameObject>(m_EventDispatcher);
	sourHitted->m_Name = "sourHitted";
	trans = sourHitted->GetComponent<TransformComponent>();
	trans->SetPosition({ -560.0f, 680.0f });
	sr = sourHitted->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto& clips7 = m_AssetManager.LoadAnimation(L"Sour_Hitted_ani", L"../Resource/Character/Sour/Sour_Hitted_ani.json");

	animComp = sourHitted->AddComponent<AnimationComponent>();
	animComp->SetAssetManager(&m_AssetManager);

	for (const auto& [clipName, clip] : clips7)
	{
		animComp->AddClip(clipName, &clip);
	}

	animComp->Play("hitted");

	sr->SetPath("../Resource/Character/Sour/Sour_Hitted_ani.json");
	sr->SetTextureKey("Sour_Hitted_ani");


	AddGameObject(sourHitted);


	auto sourJump = std::make_shared<GameObject>(m_EventDispatcher);
	sourJump->m_Name = "sourJump";
	trans = sourJump->GetComponent<TransformComponent>();
	trans->SetPosition({ -160.0f, 680.0f });
	sr = sourJump->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto& clips8 = m_AssetManager.LoadAnimation(L"Sour_Jump_Ani", L"../Resource/Character/Sour/Sour_Jump_Ani.json");

	animComp = sourJump->AddComponent<AnimationComponent>();
	animComp->SetAssetManager(&m_AssetManager);

	for (const auto& [clipName, clip] : clips8)
	{
		animComp->AddClip(clipName, &clip);
	}

	animComp->Play("jump");

	sr->SetPath("../Resource/Character/Sour/Sour_Jump_Ani.json");
	sr->SetTextureKey("Sour_Jump_Ani");


	AddGameObject(sourJump);


	auto sourKickGround = std::make_shared<GameObject>(m_EventDispatcher);
	sourKickGround->m_Name = "sourKickGround";
	trans = sourKickGround->GetComponent<TransformComponent>();
	trans->SetPosition({ 240.0f, 680.0f });
	sr = sourKickGround->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto& clips9 = m_AssetManager.LoadAnimation(L"Sour_Kick_Ground_Ani", L"../Resource/Character/Sour/Sour_Kick_Ground_Ani.json");

	animComp = sourKickGround->AddComponent<AnimationComponent>();
	animComp->SetAssetManager(&m_AssetManager);

	for (const auto& [clipName, clip] : clips9)
	{
		animComp->AddClip(clipName, &clip);
	}

	animComp->Play("kickground");

	sr->SetPath("../Resource/Character/Sour/Sour_Kick_Ground_Ani.json");
	sr->SetTextureKey("Sour_Kick_Ground_Ani");


	AddGameObject(sourKickGround);



	auto sourMarkingFail = std::make_shared<GameObject>(m_EventDispatcher);
	sourMarkingFail->m_Name = "sourMarkingFail";
	trans = sourMarkingFail->GetComponent<TransformComponent>();
	trans->SetPosition({ 640.0f, 680.0f });
	sr = sourMarkingFail->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto& clips10 = m_AssetManager.LoadAnimation(L"Sour_Marking_Fail_Ani", L"../Resource/Character/Sour/Sour_Marking_Fail_Ani.json");

	animComp = sourMarkingFail->AddComponent<AnimationComponent>();
	animComp->SetAssetManager(&m_AssetManager);

	for (const auto& [clipName, clip] : clips10)
	{
		animComp->AddClip(clipName, &clip);
	}

	animComp->Play("markingfail");

	sr->SetPath("../Resource/Character/Sour/Sour_Marking_Fail_Ani.json");
	sr->SetTextureKey("Sour_Marking_Fail_Ani");


	AddGameObject(sourMarkingFail);*/


	//auto boss = std::make_shared<GameObject>(m_EventDispatcher);
	//boss->m_Name = "boss";
	//auto bossTrans = boss->GetComponent<TransformComponent>();
	//bossTrans->SetPosition({ -900.0f, 1920.0f });
	//auto bossSR = boss->AddComponent<SpriteRenderer>();
	//bossSR->SetAssetManager(&m_AssetManager);
	//auto& bossclips = m_AssetManager.LoadAnimation(L"Boss_1Phase_Arm_UP_Hit1_Ani", "../Resource/Character/Boss/Boss_1Phase_Arm_UP_Hit1_Ani.json");

	//auto bossAnimComp = boss->AddComponent<AnimationComponent>();
	//bossAnimComp->SetAssetManager(&m_AssetManager);

	//for (const auto& [clipName, clip] : bossclips)
	//{
	//	bossAnimComp->AddClip(clipName, &clip);
	//}

	//bossAnimComp->Play("hit1");

	//bossSR->SetPath("../Resource/Character/Boss/Boss_1Phase_Arm_Up_Hit1_Ani.json");
	//bossSR->SetTextureKey("Boss_1Phase_Arm_Up_Hit1_Ani");

	//AddGameObject(boss);


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
	AddGameObject(cameraObject);
}

void CharacterScene::Finalize()
{
}

void CharacterScene::Enter()
{
}

void CharacterScene::Leave()
{
}

void CharacterScene::FixedUpdate()
{
}

void CharacterScene::Update(float deltaTime)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Update(deltaTime);
	}

	m_UIManager.Update(deltaTime);
}

void CharacterScene::Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo)
{
	if (!m_UIManager.IsFullScreenUIActive())
	{
		for (auto& pair : m_GameObjects)
		{
			auto& gameObject = pair.second;
			/*if (gameObject->IsInView(m_Camera))
			{*/
				gameObject->Render(renderInfo);
			//}
		}
	}

	m_UIManager.Render(uiRenderInfo, uiTextInfo);
}
