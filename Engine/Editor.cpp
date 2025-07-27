#include "pch.h"
#include "Editor.h"
#include "json.hpp"
#include "Scene.h"
#include "TransformComponent.h"
#include <fstream>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

void Editor::Update()
{
	ImGui::Begin("Scene Editor");

	if (!m_CurrentScene) {
		ImGui::Text("No scene loaded");
		ImGui::End();
		return;
	}

	int index = 0;

	//GameObject 리스트
	for (const auto& [key, goPtr] : m_CurrentScene->m_GameObjects)
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
		auto& go = m_CurrentScene->m_GameObjects[m_SelectedKey];
		// go는 std::shared_ptr<GameObject>
		char buf[128];
		strncpy_s(buf, go->m_Name.c_str(), sizeof(buf));
		if (ImGui::InputText("Name", buf, sizeof(buf)))
		{
			// key 변경 시 map key도 변경해야 한다면 별도 로직 필요 (주의)
			go->m_Name = buf;
		}

		if (auto* transform = go->GetComponent<TransformComponent>())
		{
			ImGui::DragFloat2("Position", &transform->m_Position.x, 0.1f);
			ImGui::DragFloat( "Rotation", &transform->m_Rotation,   0.1f);
			ImGui::DragFloat2("Scale",    &transform->m_Scale.x,    0.1f);
		}
	}

	if (ImGui::Button("Save Scene")) {
		nlohmann::json j;
		m_CurrentScene->Serialize(j);
		std::ofstream ofs("scene.json");
		ofs << j.dump(4);
	}

	if (ImGui::Button("Load Scene")) {
		nlohmann::json j;
		std::ifstream ifs("scene.json");
		ifs >> j;
		m_CurrentScene->Deserialize(j);
	}

	ImGui::End();
}

void Editor::DrawHierarchy()
{
}

void Editor::DrawInspector()
{
}
