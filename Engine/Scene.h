#pragma once
#include <unordered_map>
#include "CameraObject.h"
#include <memory>
#include <vector>
#include "RenderData.h"

class NzWndBase;
class GameObject;

class Scene
{
public:
	friend class Editor;

	Scene() = default;
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
protected:
	std::unordered_map<std::string, std::shared_ptr<GameObject>> m_GameObjects;
	CameraObject m_Camera;
	EventDispatcher& m_EventDispatcher;
private:
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator=(Scene&&) = delete;
};
