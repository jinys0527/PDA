#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "Scene.h"

class SceneManager
{
public:
	void Initialize();
	void Update(float deltaTime);
	void Render();

	std::shared_ptr<Scene> AddScene(const std::string& name, std::shared_ptr<Scene> scene);
	void SetCurrentScene(const std::string& name);
	std::shared_ptr<Scene> GetCurrentScene() const;

private:
	std::unordered_map<std::string, std::shared_ptr<Scene>> m_Scenes;
	std::shared_ptr<Scene> m_CurrentScene;
};

