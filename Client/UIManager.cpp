#include "pch.h"
#include "UIManager.h"
#include "Event.h"
#include <algorithm>
#include "UIButtonComponent.h"
#include "UISliderComponent.h"

UIManager::~UIManager()
{

}

void UIManager::Start()
{
	m_EventDispatcher.AddListener(EventType::Pressed, this);
	m_EventDispatcher.AddListener(EventType::Hovered, this);
	m_EventDispatcher.AddListener(EventType::Dragged, this);
	m_EventDispatcher.AddListener(EventType::Released, this);
}

void UIManager::OnEvent(EventType type, const void* data)
{
	auto mouseData = static_cast<const Events::MouseState*>(data);

	if (type == EventType::Pressed || type == EventType::Hovered ||
		type == EventType::Dragged || type == EventType::Released)
	{
		auto it = m_UIObjects.find(m_CurrentSceneName);
		if (it != m_UIObjects.end())
		{
			DispatchToTopUI(type, mouseData->pos, it->second);
		}
	}
}

bool UIManager::IsFullScreenUIActive() const
{
	auto it = m_UIObjects.find(m_CurrentSceneName);
	if (it == m_UIObjects.end())
		return false;

	const auto& uiMap = it->second;
	for (const auto& pair : uiMap)
	{
		const auto& uiObject = pair.second;
		if (uiObject->IsVisible() && uiObject->IsFullScreen())
			return true;
	}
	return false;
}

void UIManager::Update(float deltaTime)
{
	auto it = m_UIObjects.find(m_CurrentSceneName);
	if (it == m_UIObjects.end())
		return;

	for (auto& pair : it->second)
	{
		pair.second->Update(deltaTime);
	}
}

void UIManager::DispatchToTopUI(EventType type, const POINT& pos, std::unordered_map<std::string, std::shared_ptr<UIObject>>& uiMap)
{
	std::vector<UIObject*> sortedUI;
	sortedUI.reserve(uiMap.size());
	for (auto& pair : uiMap)
		sortedUI.push_back(pair.second.get());

	std::sort(sortedUI.begin(), sortedUI.end(), [](UIObject* a, UIObject* b) {
		return a->GetZOrder() > b->GetZOrder();
		});

	bool fullScreenUIActive = false;
	int fullScreenZ = -1;

	for (auto ui : sortedUI)
	{
		if (ui->IsVisible() && ui->IsFullScreen())
		{
			fullScreenUIActive = true;
			fullScreenZ = ui->GetZOrder();
			break;
		}
	}

	for (auto ui : sortedUI)
	{
		if (!ui->IsVisible())
			continue;

		if (fullScreenUIActive && ui->GetZOrder() < fullScreenZ)
			continue;

		// 이벤트 받을 컴포넌트 있는지 체크
		bool hasInteractableComponent = false;

		switch (type)
		{
		case EventType::Hovered:
		case EventType::Pressed:
		case EventType::Released:
			hasInteractableComponent = !ui->GetComponents<UIButtonComponent>().empty();
			break;
		case EventType::Dragged:
			hasInteractableComponent = !ui->GetComponents<UISliderComponent>().empty();
			break;
		default:
			break;
		}

		if (!hasInteractableComponent)
			continue;

		if (type != EventType::Hovered && !ui->HitCheck(pos))
			continue;

		switch (type)
		{
		case EventType::Hovered:
			for (auto btn : ui->GetComponents<UIButtonComponent>())
				btn->OnEvent(type, &pos);
			break;
		case EventType::Pressed:
		case EventType::Released:
			for (auto btn : ui->GetComponents<UIButtonComponent>())
				btn->OnEvent(type, &pos);
			for (auto slider : ui->GetComponents<UISliderComponent>())
				slider->OnEvent(type, &pos);
			break;
		case EventType::Dragged:
			for (auto slider : ui->GetComponents<UISliderComponent>())
				slider->OnEvent(type, &pos);
			break;
		default:
			break;
		}
	}
}

void UIManager::Render(std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo)
{
	auto it = m_UIObjects.find(m_CurrentSceneName);
	if (it == m_UIObjects.end())
		return;

	for (auto& pair : it->second)
	{
		if (!pair.second->IsVisible())
			continue;

		pair.second->Render(uiRenderInfo);
		pair.second->Render(uiTextInfo);
	}
}

void UIManager::Reset()
{
	m_EventDispatcher.RemoveListener(EventType::Pressed, this);
	m_EventDispatcher.RemoveListener(EventType::Hovered, this);
	m_EventDispatcher.RemoveListener(EventType::Dragged, this);
	m_EventDispatcher.RemoveListener(EventType::Released, this);
	m_UIObjects.clear();
}