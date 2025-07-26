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

	// GameObject 리스트
	for (int i = 0; i < (int)m_CurrentScene->m_GameObjects.size(); ++i) {
		auto& go = m_CurrentScene->m_GameObjects[i];
		if (ImGui::Selectable(go->m_Name.c_str(), m_SelectedIndex == i)) {
			m_SelectedIndex = i;
		}
	}

	// 선택된 GameObject 편집
	if (m_SelectedIndex >= 0 && m_SelectedIndex < (int)m_CurrentScene->m_GameObjects.size()) {
		auto& go = m_CurrentScene->m_GameObjects[m_SelectedIndex];
		char buf[128];
		strncpy_s(buf, go->m_Name.c_str(), sizeof(buf));
		if (ImGui::InputText("Name", buf, sizeof(buf))) {
			go->m_Name = buf;
		}

		// 컴포넌트 편집 (예: TransformComponent만 간단히)
		if (auto* transform = go->GetComponent<TransformComponent>()) {
			ImGui::DragFloat2("Position", &transform->m_Position.x, 0.1f);
			ImGui::DragFloat("Rotation", &transform->m_Rotation, 0.1f);
			ImGui::DragFloat2("Scale", &transform->m_Scale.x, 0.1f);
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
