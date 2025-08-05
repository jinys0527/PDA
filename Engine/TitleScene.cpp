#include "pch.h"
#include "TitleScene.h"
#include "InputManager.h"
#include "TestListener.h"
#include "GameObject.h"
#include "CameraObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "PlayerObject.h"
#include "ButtonUI.h"
#include "CameraComponent.h"
#include "UIImageComponent.h"
#include "GraffitiObject.h"
#include "GraffitiComponent.h"

void TitleScene::Initialize()
{
	auto gameObject = std::make_shared<PlayerObject>(m_EventDispatcher);
	gameObject->m_Name = "test";
	//m_EventDispatcher.AddListener()
	auto trans = gameObject->GetComponent<TransformComponent>();
	trans->SetPosition({ 960.0f, 540.0f });
	auto sr = gameObject->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
	sr->SetPath("../Resource/cat.png");
	sr->SetTextureKey("cat_texture");
	sr->SetTexture(bitmap);
	sr->SetPivotPreset(SpritePivotPreset::Center, bitmap->GetSize());


	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans3 = cameraObject->GetComponent<TransformComponent>();
	trans3->SetPosition({ 960.0f, 540.0f });
	cameraObject->GetComponent<CameraComponent>()->SetZoom(0.5);
	SetMainCamera(cameraObject);


	auto testUIObject = std::make_shared<ButtonUI>(m_EventDispatcher);
	testUIObject->m_Name = "UI";
	auto uiTrans = testUIObject->GetComponent<TransformComponent>();
	uiTrans->SetPosition({ 960, 540 });
	//sr = testUIObject->AddComponent<SpriteRenderer>();
	auto image = testUIObject->AddComponent<UIImageComponent>();
	image->SetBitmap(bitmap);
	//sr->SetAssetManager(&m_AssetManager);
	//sr->SetTexture(bitmap);
	//uiTrans->SetPivotPreset(TransformPivotPreset::Center, bitmap->GetSize());
	image->SetPivotPreset(ImagePivotPreset::Center, bitmap->GetSize());
	testUIObject->GetComponent<UIButtonComponent>()->Start();
	//uiTrans->SetScale({ 2.0f, 2.0f });
	

	//그래피티
	auto graffiti = std::make_shared<GraffitiObject>(m_EventDispatcher);
	graffiti->m_Name = "graffiti";
	auto graffitiTrans = graffiti->GetComponent<TransformComponent>();
	graffitiTrans->SetPosition({ 1600,900 });
	sr = graffiti->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	bitmap = m_AssetManager.LoadTexture(L"bird_texture", L"../Resource/redbird1.png");
	sr->SetPath("../Resource/redbird1.png");
	sr->SetTextureKey("bird_texture");
	sr->SetTexture(bitmap);
	sr->SetPivotPreset(SpritePivotPreset::Center, bitmap->GetSize());
	graffiti->GetComponent<GraffitiComponent>()->Start();



	AddGameObject(gameObject);
	AddGameObject(cameraObject);
	//AddGameObject(testUIObject);
	AddGameObject(graffiti);
}

void TitleScene::Finalize()
{
	
}

void TitleScene::Enter()
{
}

void TitleScene::Leave()
{
}

void TitleScene::Update(float deltaTime)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Update(deltaTime);
	}

	//Math::Vector2F pos = m_Camera->GetComponent<TransformComponent>()->GetPosition();
	//m_Camera->GetComponent<TransformComponent>()->SetPosition({pos.x + 100 * deltaTime, pos.y});

	//std::cout << pos.x << " " << pos.y << std::endl;
}

void TitleScene::Render(std::vector<RenderInfo>& renderInfo)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Render(renderInfo);

		
	}
}
