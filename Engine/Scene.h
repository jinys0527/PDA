#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include "RenderData.h"
#include "AssetManager.h"
#include "SoundAssetManager.h"
#include "SoundManager.h"

class NzWndBase;
class GameObject;
class CameraObject;

class Scene
{
public:
	friend class Editor;

	Scene(EventDispatcher& eventDispatcher, AssetManager& assetManager, SoundAssetManager& soundAssetManager, SoundManager& soundManager) : m_EventDispatcher(eventDispatcher), m_AssetManager(assetManager), m_SoundAssetManager(soundAssetManager), m_SoundManager(soundManager) {}
	virtual ~Scene();
	virtual void Initialize() = 0;
	virtual void Finalize() = 0;

	virtual void Enter() = 0;
	virtual void Leave() = 0;

	virtual void FixedUpdate() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(std::vector<RenderInfo>& renderInfo) = 0;

	void AddGameObject(std::shared_ptr<GameObject> gameObject);
	void RemoveGameObject(std::shared_ptr<GameObject> gameObject);

	void SetMainCamera(std::shared_ptr<GameObject> gameObject);
	CameraObject* GetMainCamera() { return m_Camera; }

	void Serialize(nlohmann::json& j) const;
	void Deserialize(const nlohmann::json& j);

	void SetName(std::string name) { m_Name = name; }
	std::string GetName() const { return m_Name; }

protected:
	std::unordered_map<std::string, std::shared_ptr<GameObject>> m_GameObjects;
	EventDispatcher& m_EventDispatcher;
	AssetManager& m_AssetManager;
	SoundAssetManager& m_SoundAssetManager;
	SoundManager& m_SoundManager;
	CameraObject* m_Camera;
	std::string m_Name;
private:
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator=(Scene&&) = delete;
};
