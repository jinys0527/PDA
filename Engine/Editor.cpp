#include "pch.h"
#include "Editor.h"
#include "json.hpp"
#include "Scene.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Obstacle.h"
#include "ItemObject.h"
#include <fstream>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include "SpriteRenderer.h"

void Editor::Update()
{
	auto currentScene = m_SceneManager.GetCurrentScene();
	if (!currentScene) {
		ImGui::Text("No scene loaded");
		ImGui::End();
		return;
	}

	DrawSceneList();

	CameraControl(currentScene);

	SaveAndLoadFile(currentScene);

	DrawGameObjectHierarchy(currentScene);

	DrawGameObjectInspector(currentScene);
}

void Editor::DrawSceneList()
{
	std::string selectedScene = "";
	ImGui::Begin("Scene List");
	//Scene ����Ʈ
	for (const auto& [key, goPtr] : m_SceneManager.m_Scenes)
	{
		bool isSelected = (selectedScene == key);
		if (ImGui::Selectable(key.c_str(), isSelected))
		{
			selectedScene = key;
			m_SceneManager.SetCurrentScene(key);
		}
	}
	ImGui::End();
}

void Editor::SaveAndLoadFile(std::shared_ptr<Scene> currentScene)
{
	std::string fileName = currentScene->GetName() + ".json";

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			// �޴� �������� ������ �г� ���� �÷��� ���
			if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
			{
				nlohmann::json j;
				currentScene->Serialize(j);
				std::ofstream ofs(fileName);
				ofs << j.dump(4);
			}
			if (ImGui::MenuItem("Load Scene", "Ctrl+O"))
			{
				nlohmann::json j;
				std::ifstream ifs(fileName);
				ifs >> j;
				currentScene->Deserialize(j);
			}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}

	ImGuiIO& io = ImGui::GetIO();
	if (io.KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_S)) // Ctrl+S
	{
		nlohmann::json j;
		currentScene->Serialize(j);
		std::ofstream ofs(fileName);
		ofs << j.dump(4);
	}

	if (io.KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_O)) // Ctrl+O
	{
		nlohmann::json j;
		std::ifstream ifs(fileName);
		ifs >> j;
		currentScene->Deserialize(j);
	}
}

void Editor::CameraControl(std::shared_ptr<Scene> currentScene)
{
	ImGui::Begin("CameraControl");
	ImGui::Text("Camera Offset");
	auto cameraTrans = currentScene->GetMainCamera()->GetComponent<TransformComponent>();
	Math::Vector2F cameraPos = cameraTrans->GetPosition();
	if (ImGui::DragFloat2("Offset", &cameraPos.x, 1.0f))
	{
		cameraTrans->SetPosition(cameraPos);
	}// ���� �̵�

	if (ImGui::SliderFloat("Offset X", &cameraPos.x, 960.0f, 500000.0f))
	{
		cameraTrans->SetPosition(cameraPos);
	}
	if (ImGui::SliderFloat("Offset Y", &cameraPos.y, 540.0f, 1000.0f))
	{
		cameraTrans->SetPosition(cameraPos);
	}
	ImGui::End();
}

void Editor::DrawGameObjectHierarchy(std::shared_ptr<Scene> currentScene)
{
	int index = 0;

	std::vector<std::pair<std::string, std::shared_ptr<GameObject>>> sortedObjects;

	// map -> vector ����
	for (const auto& kv : currentScene->m_GameObjects)
		sortedObjects.push_back(kv);

	std::sort(sortedObjects.begin(), sortedObjects.end(),
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
		}
	);

	ImGui::Begin("Hierarchy");
	for (const auto& [key, goPtr] : sortedObjects)
	{
		bool selected = (m_SelectedKey == key);
		if (ImGui::Selectable(key.c_str(), selected))
		{
			m_SelectedKey = key;
			m_SelectedIndex = index;
		}
		++index;
	}
	ImGui::End();
}

void Editor::DrawGameObjectInspector(std::shared_ptr<Scene> currentScene)
{
	// ���õ� GameObject ����
	ImGui::Begin("Inspector");

	if (!m_SelectedKey.empty())
	{
		auto gameObject = currentScene->m_GameObjects[m_SelectedKey];
		// gameObject�� std::shared_ptr<GameObject>
		char buf[128];
		strncpy_s(buf, gameObject->m_Name.c_str(), sizeof(buf));
		if (ImGui::InputText("Name", buf, sizeof(buf)))
		{
			// key ���� �� map key�� �����ؾ� �Ѵٸ� ���� ���� �ʿ� (����)
			currentScene->RemoveGameObject(gameObject);
			gameObject->m_Name = buf;
			currentScene->AddGameObject(gameObject);
			m_SelectedKey = gameObject->m_Name;
		}

		if (auto* obstacle = dynamic_cast<Obstacle*>(gameObject.get()))
		{
			int lane = static_cast<int>(obstacle->GetZ());
			if (ImGui::SliderInt("Lane", &lane, 0, 2))
			{
				obstacle->SetZ(static_cast<float>(lane));
			}
		}

		if (auto* item = dynamic_cast<ItemObject*>(gameObject.get()))
		{
			int lane = static_cast<int>(item->GetZ());
			if (ImGui::SliderInt("Lane", &lane, 0, 2))
			{
				item->SetZ(static_cast<float>(lane));
			}
		}

		auto* spriteRenderer = gameObject->GetComponent<SpriteRenderer>();
		if (spriteRenderer)
		{
			float opacity = spriteRenderer->GetOpacity();

			if (ImGui::SliderFloat("Opacity", &opacity, 0.0f, 1.0f))
			{
				spriteRenderer->SetOpacity(opacity);
			}
		}


		auto* transform = gameObject->GetComponent<TransformComponent>();

		if (transform)
		{
			Math::Vector2F pos = transform->GetPosition();
			float rot = transform->GetRotation();
			Math::Vector2F scale = transform->GetScale();

			if (ImGui::DragFloat2("Position##Transform", &pos.x, 0.1f))
			{
				transform->SetPosition(pos);
			}
			if (ImGui::DragFloat("Rotation##Transform", &rot, 0.1f))
			{
				transform->SetRotation(rot);
			}
			if (ImGui::DragFloat2("Scale##Transform", &scale.x, 0.1f))
			{
				transform->SetScale(scale);
			}
		}
	}
	ImGui::End();
}
