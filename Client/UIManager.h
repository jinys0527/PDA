#pragma once
#include "IEventListener.h"
#include <vector>
#include <memory>
#include <windows.h>
#include "RenderData.h"
#include "UIObject.h"

class UIManager : public IEventListener
{
public:
	void AddUI(std::shared_ptr<UIObject> uiObject)
	{
		m_UIObjects[uiObject->m_Name] = uiObject;
	}

	void RemoveUI(std::shared_ptr<UIObject> uiObject)
	{
		auto it = m_UIObjects.find(uiObject->m_Name);
		if (it != m_UIObjects.end())
		{
			m_UIObjects.erase(uiObject->m_Name);
		}
	}

	void OnEvent(EventType type, const void* data) override;

	bool IsFullScreenUIActive() const;

	void Update(float deltaTime);

	void Render(std::vector<UIRenderInfo>& renderInfo, std::vector<UITextInfo>& textInfo);

private:
	void DispatchToTopUI(EventType type, const POINT& pos);
	std::unordered_map<std::string, std::shared_ptr<UIObject>> m_UIObjects;
};

