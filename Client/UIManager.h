#pragma once
#include "IEventListener.h"
#include <vector>
#include <memory>
#include <windows.h>
#include "RenderData.h"
#include "UIObject.h"
#include "EventDispatcher.h"

class UIManager : public IEventListener
{
public:
	UIManager(EventDispatcher& eventDispatcher) : m_EventDispatcher(eventDispatcher) {}
	virtual ~UIManager();

	void AddUI(std::string sceneName, std::shared_ptr<UIObject> uiObject)
	{
		m_UIObjects[sceneName][uiObject->m_Name] = uiObject;
	}

	void RemoveUI(std::string sceneName, std::shared_ptr<UIObject> uiObject)
	{
		auto it = m_UIObjects.find(sceneName);
		if (it != m_UIObjects.end())
		{
			auto& uiMap = it->second;
			auto it2 = uiMap.find(uiObject->m_Name);
			if (it2 != uiMap.end())
			{
				uiMap.erase(it2);
				if (uiMap.empty())  // 씬 내 UI가 다 지워지면 씬 키도 지울 수 있음 (선택 사항)
				{
					m_UIObjects.erase(it);
				}
			}
		}
	}

	void OnEvent(EventType type, const void* data) override;

	bool IsFullScreenUIActive() const;

	void Update(float deltaTime);

	void Render(std::vector<UIRenderInfo>& renderInfo, std::vector<UITextInfo>& textInfo);

	void Start();

	void Reset();

	void SetCurrentScene(std::string currentSceneName) 
	{
		m_CurrentSceneName = currentSceneName;
	}

	std::string GetCurrentScene() const
	{
		return m_CurrentSceneName;
	}

	std::unordered_map <std::string, std::unordered_map<std::string, std::shared_ptr<UIObject>>>& GetUIObjects()
	{
		return m_UIObjects;
	}

private:
	EventDispatcher& m_EventDispatcher; 
	std::string m_CurrentSceneName;
	void DispatchToTopUI(EventType type, const POINT& pos, std::unordered_map<std::string, std::shared_ptr<UIObject>>& uiMap);
	std::unordered_map <std::string, std::unordered_map<std::string, std::shared_ptr<UIObject>>> m_UIObjects;
};

