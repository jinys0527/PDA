#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "Scene.h"
#include "D2DRenderer.h"
#include "EventDispatcher.h"
#include "AssetManager.h"
#include "SoundAssetManager.h"
#include "CameraObject.h"
#include "SoundManager.h"

class SceneManager
{
	friend class Editor;
public:
	SceneManager(D2DRenderer& renderer, EventDispatcher& eventDispatcher, AssetManager& assetManager, SoundAssetManager& soundAssetManager, SoundManager& soundManager) : m_Renderer(renderer), m_EventDispatcher(eventDispatcher), m_AssetManager(assetManager), m_SoundAssetManager(soundAssetManager), m_SoundManager(soundManager) { }
	~SceneManager() { m_Renderer.LogInternalComStates(); }

	void Initialize();
	void Update(float deltaTime);
	void Render();

	void SetCamera(CameraObject* camera) { m_Camera = camera; }
	CameraObject* GetCamera() { return m_Camera; }

	std::shared_ptr<Scene> AddScene(const std::string& name, std::shared_ptr<Scene> scene);
	void SetCurrentScene(const std::string& name);
	std::shared_ptr<Scene> GetCurrentScene() const;

private:
	std::unordered_map<std::string, std::shared_ptr<Scene>> m_Scenes;
	std::shared_ptr<Scene> m_CurrentScene;
	CameraObject* m_Camera;
	D2DRenderer& m_Renderer;
	AssetManager& m_AssetManager;
	SoundAssetManager& m_SoundAssetManager;
	EventDispatcher& m_EventDispatcher;
	SoundManager& m_SoundManager;
};

