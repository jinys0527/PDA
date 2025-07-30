#include "pch.h"
#include "TitleScene.h"
#include "InputManager.h"
#include "TestListener.h"
#include "GameObject.h"
#include "CameraObject.h"
#include "TransformComponent.h"
#include "SpriteRenderer.h"
#include "PlayerObject.h"

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
	SetMainCamera(cameraObject);

	AddGameObject(gameObject);
	AddGameObject(cameraObject);
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
}

void TitleScene::Render(std::vector<RenderInfo>& renderInfo)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Render(renderInfo);
	}
}
