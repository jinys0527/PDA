#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "InGameUITestScene.h"
#include "RenderData.h"

void SceneManager::Initialize()
{
	m_SoundManager.Init();
	auto testScene = AddScene("TestScene", std::make_shared<TestScene>(m_EventDispatcher, m_AssetManager, m_SoundAssetManager, m_SoundManager, m_Renderer, m_UIManager));
	testScene->SetSceneManager(this);
//  auto titleScene = AddScene("TitleScene", std::make_shared<TitleScene>(m_EventDispatcher, m_AssetManager, m_SoundAssetManager, m_SoundManager, m_Renderer, m_UIManager));
// 	titleScene->SetSceneManager(this);
	auto inGameUITestScene = AddScene("InGameUITestScene", std::make_shared<InGameUITestScene>(m_EventDispatcher, m_AssetManager, m_SoundAssetManager, m_SoundManager, m_Renderer, m_UIManager));
	inGameUITestScene->SetSceneManager(this);

	testScene->Initialize();
	//testScene->SetName("TestScene");
	//titleScene->Initialize();
	//titleScene->SetName("TitleScene");
	inGameUITestScene->Initialize();
	inGameUITestScene->SetName("InGameUITestScene");

	SetCurrentScene("InGameUITestScene");
}

void SceneManager::Update(float deltaTime)
{
	static float totalTime = 0;
	totalTime += deltaTime;
	if (totalTime >= 0.016f)
		m_CurrentScene->FixedUpdate();
	m_CurrentScene->Update(deltaTime);
}

void SceneManager::Render()
{
	std::vector<RenderInfo> renderInfo;
	std::vector<UIRenderInfo> uiRenderInfo;
	std::vector<UITextInfo> uiTextInfo;
	m_CurrentScene->Render(renderInfo, uiRenderInfo, uiTextInfo);
	m_Renderer.Draw(renderInfo, uiRenderInfo, uiTextInfo);
}

std::shared_ptr<Scene> SceneManager::AddScene(const std::string& name, std::shared_ptr<Scene> scene)
{
	m_Scenes[name] = scene;

	m_Scenes[name]->SetGameManager(&m_GameManager);

	return m_Scenes[name];
}

void SceneManager::SetCurrentScene(const std::string& name)
{
	auto it = m_Scenes.find(name);
	if (it != m_Scenes.end())
	{
		if (m_CurrentScene)
		{
			m_CurrentScene->Leave();
		}

		m_CurrentScene = it->second;
		m_CurrentScene->Enter();

		m_Camera = m_CurrentScene->GetMainCamera();
		m_Renderer.SetCamera(m_Camera);
	}
}

std::shared_ptr<Scene> SceneManager::GetCurrentScene() const
{
	return m_CurrentScene;
}

void SceneManager::ChangeScene(const std::string& name)
{
	if(m_CurrentScene)
		m_CurrentScene->Leave();
	auto it = m_Scenes.find(name);
	if (it != m_Scenes.end())
	{
		m_CurrentScene = it->second;
		m_CurrentScene->Enter();
		m_Camera = m_CurrentScene->GetMainCamera();
		m_Renderer.SetCamera(m_Camera);
	}
}
