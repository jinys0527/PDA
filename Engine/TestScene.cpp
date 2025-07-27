#include "pch.h"
#include "TestScene.h"
#include "GameObject.h"

void TestScene::Initialize(NzWndBase* pWnd)
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
}

void TestScene::Render(HDC hDC)
{
	for (auto gameObject : m_GameObjects)
	{
		//gameObject->Render();
	}
}
