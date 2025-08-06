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

void TestScene::Initialize()
{
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
	trans3->SetPosition({ 960.0f, 540.0f });
	cameraObject->GetComponent<CameraComponent>()->SetZoom(0.5f);
	SetMainCamera(cameraObject);



	auto teleobj = std::make_shared<Telegraph>(m_EventDispatcher);
	auto sr = teleobj->AddComponent<SpriteRenderer>();
	sr->SetTexture(m_AssetManager.LoadTexture(L"brick", L"../Resource/bricks.png"));
	sr->SetPivotPreset(SpritePivotPreset::Center, sr->GetTexture()->GetSize());
	sr->SetOpacity(0.0f);
	//teleobj->SetActive();









	AddUIObject(soundUI);
	AddGameObject(cameraObject);
	AddGameObject(teleobj);
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
