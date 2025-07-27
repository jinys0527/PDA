#pragma once

class Scene;

class Editor
{
public:
	void SetScene(Scene* scene) { m_CurrentScene = scene; }
	void Update();
private:
	void DrawHierarchy();
	void DrawInspector();

private:
	Scene* m_CurrentScene;
	std::string m_SelectedKey;
	int m_SelectedIndex = -1;
};

