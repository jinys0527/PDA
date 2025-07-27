#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "Scene.h"
#include "D2DRenderer.h"
#include "EventDispatcher.h"

class SceneManager
{
public:
	SceneManager(D2DRenderer& renderer, EventDispatcher& eventDispatcher) : m_Renderer(renderer), m_EventDispatcher(eventDispatcher) {}
	~SceneManager() = default;

	void Initialize();
	void Update(float deltaTime);
	void Render();

	std::shared_ptr<Scene> AddScene(const std::string& name, std::shared_ptr<Scene> scene);
	void SetCurrentScene(const std::string& name);
	std::shared_ptr<Scene> GetCurrentScene() const;

private:
	std::unordered_map<std::string, std::shared_ptr<Scene>> m_Scenes;
	std::shared_ptr<Scene> m_CurrentScene;
	D2DRenderer& m_Renderer;
	EventDispatcher& m_EventDispatcher;
};

