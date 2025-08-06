#include "pch.h"
#include "Scene.h"
#include "json.hpp"
#include "GameObject.h"
#include "UIObject.h"
#include "CameraObject.h"
#include <unordered_set>

Scene::~Scene()
{
	m_GameObjects.clear();
	m_Camera = nullptr; // �ʿ� ��
}

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject)
{
	if (gameObject->m_Name == "Camera")
	{
		SetMainCamera(gameObject);
	}
	m_GameObjects[gameObject->m_Name] = gameObject;
}

void Scene::RemoveGameObject(std::shared_ptr<GameObject> gameObject)
{
	auto it = m_GameObjects.find(gameObject->m_Name);
	if (it != m_GameObjects.end())
	{
		m_GameObjects.erase(gameObject->m_Name);
	}
}

void Scene::AddUIObject(std::shared_ptr<UIObject> uiObject)
{
	m_UIObjects[uiObject->m_Name] = uiObject;
}

void Scene::RemoveUIObject(std::shared_ptr<UIObject> uiObject)
{
	auto it = m_UIObjects.find(uiObject->m_Name);
	if (it != m_UIObjects.end())
	{
		m_UIObjects.erase(uiObject->m_Name);
	}
}

void Scene::SetMainCamera(std::shared_ptr<GameObject> gameObject)
{
	m_Camera = dynamic_cast<CameraObject*>(gameObject.get());
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
	std::unordered_set<std::string> jsonNames;
	for (const auto& gameObjectJson : j.at("gameObjects"))
	{
		jsonNames.insert(gameObjectJson.at("name").get<std::string>());
	}

	// ������ ������ ������Ʈ ����
	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); )
	{
		if (jsonNames.find(it->first) == jsonNames.end())
		{
			it = m_GameObjects.erase(it);
		}
		else
		{
			++it;
		}
	}

	// JSON ������Ʈ ���� ���� ������Ʈ�� ������ Deserialize, ������ �� ����
	for (const auto& gameObjectJson : j.at("gameObjects"))
	{
		std::string name = gameObjectJson.at("name");
		auto it = m_GameObjects.find(name);
		if (it != m_GameObjects.end())
		{
			// ���� ������Ʈ�� ������ ���� ���¸� ����
			it->second->Deserialize(gameObjectJson);
		}
		else
		{
			// ������ ���� ���� �� �߰�
			auto gameObject = std::make_shared<GameObject>(m_EventDispatcher);
			gameObject->Deserialize(gameObjectJson);
			m_GameObjects[name] = std::move(gameObject);
		}
	}
}
