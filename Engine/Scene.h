#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include "RenderData.h"
#include "AssetManager.h"

class NzWndBase;
class GameObject;

class Scene
{
public:
	friend class Editor;

	Scene(EventDispatcher& eventDispatcher, AssetManager& assetManager) : m_EventDispatcher(eventDispatcher), m_AssetManager(assetManager) {}
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

	void Serialize(nlohmann::json& j) const;
	void Deserialize(const nlohmann::json& j);

	Math::Vector2F m_ViewOffset = { 0.0f, 0.0f };
protected:
	std::unordered_map<std::string, std::shared_ptr<GameObject>> m_GameObjects;
	EventDispatcher& m_EventDispatcher;
	AssetManager& m_AssetManager;
private:
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator=(Scene&&) = delete;
};
