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
#include "BlackBoard.h"

void TitleScene::Initialize()
{
	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans3 = cameraObject->GetComponent<TransformComponent>();
	trans3->SetPosition({ 960.0f, 540.0f });
	cameraObject->GetComponent<CameraComponent>()->SetZoom(0.5);
	SetMainCamera(cameraObject);

	BlackBoard bb;

	// 값 설정
	bb.SetValue("HP", 100);
	bb.SetValue("IsEnemyVisible", true);
	bb.SetValue("EnemyName", std::string("Orc"));

	// 값 가져오기
	if (auto hp = bb.GetValue<int>("HP")) {
		std::cout << "HP: " << *hp << "\n";
	}

	if (auto visible = bb.GetValue<bool>("IsEnemyVisible")) {
		std::cout << "적이 보임? " << std::boolalpha << *visible << "\n";
	}

	if (auto name = bb.GetValue<std::string>("EnemyName")) {
		std::cout << "적 이름: " << *name << "\n";
	}
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
