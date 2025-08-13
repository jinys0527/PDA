#include "pch.h"
#include "Scene.h"
#include "json.hpp"
#include "GameObject.h"
#include "UIObject.h"
#include "ItemObject.h"
#include "Obstacle.h"
#include "CameraObject.h"
#include "GameManager.h"
#include <unordered_set>
#include "SpriteRenderer.h"
#include "AnimationComponent.h"
#include "TransformComponent.h"

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
	m_GameObjects[gameObject->m_Name] = std::move(gameObject);
}

void Scene::RemoveGameObject(std::shared_ptr<GameObject> gameObject)
{
	auto it = m_GameObjects.find(gameObject->m_Name);
	if (it != m_GameObjects.end())
	{
		gameObject->GetComponent<TransformComponent>()->DetachFromParent();
		m_GameObjects.erase(gameObject->m_Name);
	}
}

void Scene::SetMainCamera(std::shared_ptr<GameObject> gameObject)
{
	m_Camera = dynamic_cast<CameraObject*>(gameObject.get());
}

void Scene::Serialize(nlohmann::json& j) const
{
	j["gameObjects"] = nlohmann::json::array();

	// map -> vector ����
	std::vector<std::pair<std::string, std::shared_ptr<GameObject>>> vec(
		m_GameObjects.begin(), m_GameObjects.end());

	// ���� (���� ���� �̸� ����)
	std::sort(vec.begin(), vec.end(),
		[](const auto& a, const auto& b) {
			auto extractNameAndNumber = [](const std::string& s) -> std::pair<std::string, int> {
				size_t pos = s.find_first_of("0123456789");
				if (pos != std::string::npos) {
					return { s.substr(0, pos), std::stoi(s.substr(pos)) };
				}
				return { s, -1 };
				};

			auto [nameA, numA] = extractNameAndNumber(a.first);
			auto [nameB, numB] = extractNameAndNumber(b.first);

			if (nameA == nameB) {
				// ���� ������ ��� ���� ��
				return numA < numB;
			}
			// �̸�(����) ���� ��
			return nameA < nameB;
		});

	// ���ĵ� ������� JSON�� ����
	for (const auto& gameObject : vec)
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

	// JSON ������Ʈ ���� ���� ������Ʈ�� ������ Deserialize, ������ �� ����
	for (const auto& gameObjectJson : j.at("gameObjects"))
	{
		std::string name = gameObjectJson.at("name");
		auto it = m_GameObjects.find(name);
		if (it != m_GameObjects.end())
		{
			auto sr = it->second->GetComponent<SpriteRenderer>();
			if(sr)
				sr->SetAssetManager(&m_AssetManager);
			auto animComp = it->second->GetComponent<AnimationComponent>();
			if (animComp)
				animComp->SetAssetManager(&m_AssetManager);
			// ���� ������Ʈ�� ������ ���� ���¸� ����
			it->second->Deserialize(gameObjectJson);
		}
		else
		{
			std::shared_ptr<GameObject> gameObject;
			// ������ ���� ���� �� �߰�
			if (name.find("Obstacle"))
			{
				gameObject = std::make_shared<Obstacle>(m_EventDispatcher);
			}
			else if (name.find("Item"))
			{
				gameObject = std::make_shared<ItemObject>(m_EventDispatcher);
			}
			else
			{
				gameObject = std::make_shared<GameObject>(m_EventDispatcher);
			}
			
			gameObject->Deserialize(gameObjectJson);
			m_GameObjects[name] = std::move(gameObject);
		}
	}
}

void Scene::SetGameManager(GameManager* gameManager)
{
	m_GameManager = gameManager;
}

void Scene::SetSceneManager(SceneManager* sceneManager)
{
	m_SceneManager = sceneManager;
}
