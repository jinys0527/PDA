#include "pch.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "RenderData.h"

void SceneManager::Initialize()
{
	auto testScene = AddScene("TestScene", std::make_shared<TestScene>(m_EventDispatcher, m_AssetManager));
	auto titleScene = AddScene("TitleScene", std::make_shared<TitleScene>(m_EventDispatcher, m_AssetManager));
	
	testScene->Initialize();
	titleScene->Initialize();
	titleScene->SetName("TitleScene");
	testScene->SetName("TestScene");

	SetCurrentScene("TitleScene");
}

void SceneManager::Update(float deltaTime)
{
	m_CurrentScene->Update(deltaTime);
}

void SceneManager::Render()
{
	std::vector<RenderInfo> renderInfo;
	m_CurrentScene->Render(renderInfo);
	m_Renderer.Draw(renderInfo);
}

std::shared_ptr<Scene> SceneManager::AddScene(const std::string& name, std::shared_ptr<Scene> scene)
{
	m_Scenes[name] = scene;

	return m_Scenes[name];
}

void SceneManager::SetCurrentScene(const std::string& name)
{
	auto it = m_Scenes.find(name);
	if (it != m_Scenes.end())
	{
		m_CurrentScene = it->second;
		m_Camera = m_CurrentScene->GetMainCamera();
		m_Renderer.SetCamera(m_Camera);
	}
}

std::shared_ptr<Scene> SceneManager::GetCurrentScene() const
{
	return m_CurrentScene;
}