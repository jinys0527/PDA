#include "pch.h"
#include "Editor.h"
#include "json.hpp"
#include "Scene.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include <fstream>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

void Editor::Update()
{
	ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(300, 600), ImGuiCond_Always);
	ImGui::Begin("Scene Editor");

	auto currentScene = m_SceneManager.GetCurrentScene();
	if (!currentScene) {
		ImGui::Text("No scene loaded");
		ImGui::End();
		return;
	}

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			// 메뉴 아이템을 누르면 패널 열기 플래그 토글
			if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
			{
				nlohmann::json j;
				currentScene->Serialize(j);
				std::ofstream ofs("scene.json");
				ofs << j.dump(4);
			}
			if (ImGui::MenuItem("Load Scene", "Ctrl+O"))
			{
				nlohmann::json j;
				std::ifstream ifs("scene.json");
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
		std::ofstream ofs("scene.json");
		ofs << j.dump(4);
	}

	if (io.KeyCtrl && ImGui::IsKeyPressed(ImGuiKey_O)) // Ctrl+O
	{
		nlohmann::json j;
		std::ifstream ifs("scene.json");
		ifs >> j;
		currentScene->Deserialize(j);
	}

	int index = 0;

	ImGui::Separator();
	ImGui::Text("Camera Offset");
	auto cameraTrans = currentScene->GetMainCamera()->GetComponent<TransformComponent>();
	Math::Vector2F cameraPos = cameraTrans->GetPosition();
	if (ImGui::DragFloat2("Offset", &cameraPos.x, 1.0f))
	{
		cameraTrans->SetPosition(cameraPos);
	}// 수동 이동

	if (ImGui::SliderFloat("Offset X", &cameraPos.x, -1000.0f, 1000.0f))
	{
		cameraTrans->SetPosition(cameraPos);
	}
	if (ImGui::SliderFloat("Offset Y", &cameraPos.y, -1000.0f, 1000.0f))
	{
		cameraTrans->SetPosition(cameraPos);
	}

	//GameObject 리스트
	for (const auto& [key, goPtr] : currentScene->m_GameObjects)
	{
		bool selected = (m_SelectedKey == key);
		if (ImGui::Selectable(key.c_str(), selected))
		{
			m_SelectedKey = key;
			m_SelectedIndex = index;
		}
		++index;
	}

	// 선택된 GameObject 편집
	if (!m_SelectedKey.empty())
	{
		auto& go = currentScene->m_GameObjects[m_SelectedKey];
		// go는 std::shared_ptr<GameObject>
		char buf[128];
		strncpy_s(buf, go->m_Name.c_str(), sizeof(buf));
		if (ImGui::InputText("Name", buf, sizeof(buf)))
		{
			// key 변경 시 map key도 변경해야 한다면 별도 로직 필요 (주의)
			currentScene->RemoveGameObject(go);
			go->m_Name = buf;
			currentScene->AddGameObject(go);
		}

		
		auto* transform = go->GetComponent  <TransformComponent>();
		
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

void Editor::DrawHierarchy()
{
}

void Editor::DrawInspector()
{
}
