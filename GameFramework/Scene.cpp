#include "pch.h"
#include "Scene.h"
#include "json.hpp"

Scene::~Scene()
{
}

void Scene::Serialize(nlohmann::json& j) const
{
	j["gameObjects"] = nlohmann::json::array();
	for (const auto& gameObject : m_GameObjects)
	{
		nlohmann::json gameObjectJson;
		gameObject.second->Serialize(gameObjectJson);
		j["gameObjects"].push_back(gameObjectJson);
	}
}

void Scene::Deserialize(const nlohmann::json& j)
{
	m_GameObjects.clear();
	for (const auto& gameObjectJson : j.at("gameObjects"))
	{
		auto gameObject = std::make_shared<GameObject>(m_EventDispatcher);
		gameObject->Deserialize(gameObjectJson);
		m_GameObjects[gameObject->m_Name] = std::move(gameObject);
	}
}
