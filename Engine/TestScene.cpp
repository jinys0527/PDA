#include "pch.h"
#include "TestScene.h"
#include "GameObject.h"

void TestScene::Initialize()
{
	std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(m_EventDispatcher);
	gameObject->m_Name = "test";
	AddGameObject(gameObject);
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
