#include "pch.h"
#include "TestScene.h"
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "TransformComponent.h"

void TestScene::Initialize()
{
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(m_EventDispatcher);
	gameObject->m_Name = "test";
	auto trans = gameObject->GetComponent<TransformComponent>();
	trans->SetPosition({ 300.0f, 300.0f });
	auto sr = gameObject->AddComponent<SpriteRenderer>();
	auto bitmap = m_AssetManager.LoadTexture(L"cat_texture", L"../Resource/cat.png");
	sr->SetPath("../Resource/cat.png");
	sr->SetTextureKey("cat_texture");

	std::shared_ptr<GameObject> gameObject2 = std::make_shared<GameObject>(m_EventDispatcher);
	gameObject2->m_Name = "test2";
	auto trans2 = gameObject2->GetComponent<TransformComponent>();
	trans2->SetPosition({ 800.0f, 500.0f });
	auto sr2 = gameObject2->AddComponent<SpriteRenderer>();
	sr2->SetPath("../Resource/cat.png");
	sr2->SetTextureKey("cat_texture");

	sr->SetTexture(bitmap);
	sr2->SetTexture(bitmap);
	AddGameObject(gameObject);
	AddGameObject(gameObject2);
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
