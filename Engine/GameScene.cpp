#include "pch.h"
#include "GameScene.h"
#include "InputManager.h"
#include "ControlComponent.h"
#include "ButtonUI.h"
#include "GameObject.h"
#include "UIObject.h"
#include "SceneManager.h"
#include "CameraObject.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "RectTransformComponent.h"
#include "BoxColliderComponent.h"
#include "SoundUI.h"
#include "UIImageComponent.h"

void GameScene::Initialize()
{

#pragma region Camera
	auto cameraObject = std::make_shared<CameraObject>(m_EventDispatcher, 1920.0f, 1080.0f);
	cameraObject->m_Name = "Camera";
	auto trans = cameraObject->GetComponent<TransformComponent>();
	trans->SetPosition({ 960.0f, 540.0f });
	cameraObject->GetComponent<CameraComponent>()->SetZoom(0.5f);
	BoxColliderComponent* cameraCol = cameraObject->AddComponent<BoxColliderComponent>();
	cameraCol->Start();
	cameraCol->SetSize({ 1920, 1080 });
	SetMainCamera(cameraObject);

	AddGameObject(cameraObject);
#pragma endregion
}

void GameScene::Finalize()
{
	m_UIManager.GetUIObjects().erase("GameScene");
}

void GameScene::Enter()
{
}

void GameScene::Leave()
{
}

void GameScene::FixedUpdate()
{
}

void GameScene::Update(float deltaTime)
{
	for (auto gameObject : m_GameObjects)
	{
		gameObject.second->Update(deltaTime);
	}

	m_UIManager.Update(deltaTime);
}

void GameScene::Render(std::vector<RenderInfo>& renderInfo, std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo)
{
	if (!m_UIManager.IsFullScreenUIActive())
	{
		for (auto& pair : m_GameObjects)
		{
			auto& gameObject = pair.second;
			if (gameObject->IsInView(m_Camera))
			{
				gameObject->Render(renderInfo);
			}
		}
	}

	m_UIManager.Render(uiRenderInfo, uiTextInfo);
}
