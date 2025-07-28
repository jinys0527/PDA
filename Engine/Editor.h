#pragma once
#include "SceneManager.h"

class Editor
{
public:
	Editor(SceneManager& sceneManager) : m_SceneManager(sceneManager) {}
	void Update();
private:
	void DrawHierarchy();
	void DrawInspector();

private:
	SceneManager& m_SceneManager;;
	std::string m_SelectedKey;
	int m_SelectedIndex = -1;
};

