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

void TestScene::Initialize()
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

void TestScene::FixedUpdate()
{

}

void TestScene::Update(float deltaTime)
{
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
