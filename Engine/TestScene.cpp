#include "pch.h"
#include "TestScene.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"
#include "BoxColliderComponent.h"
#include "CameraObject.h"

void TestScene::Initialize()
{
	auto gameObject = std::make_shared<GameObject>(m_EventDispatcher);
	gameObject->m_Name = "test";
	auto trans = gameObject->GetComponent<TransformComponent>();
	trans->SetPosition({ 300.0f, 300.0f });
	auto sr = gameObject->AddComponent<SpriteRenderer>();
	sr->SetAssetManager(&m_AssetManager);
	auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
	sr->SetPath("../Resource/cat.png");
	sr->SetTextureKey("cat_texture");

	auto gameObject2 = std::make_shared<GameObject>(m_EventDispatcher);
	gameObject2->m_Name = "test2";
	auto trans2 = gameObject2->GetComponent<TransformComponent>();
	trans2->SetPosition({ 800.0f, 500.0f });
	auto sr2 = gameObject2->AddComponent<SpriteRenderer>();
	sr2->SetAssetManager(&m_AssetManager);
	sr2->SetPath("../Resource/cat.png");
	sr2->SetTextureKey("cat_texture");

	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans3 = cameraObject->GetComponent<TransformComponent>();
	trans3->SetPosition({ 960.0f, 540.0f });
	SetMainCamera(cameraObject);

	sr->SetTexture(bitmap);
	sr2->SetTexture(bitmap);
	AddGameObject(gameObject);
	AddGameObject(gameObject2);
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


}

void TestScene::Render(std::vector<RenderInfo>& renderInfo)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Render(renderInfo);
	}
}
