#include "pch.h"
#include "UIManager.h"
#include "Event.h"
#include <algorithm>
#include "UIButtonComponent.h"
#include "UISliderComponent.h"

void UIManager::OnEvent(EventType type, const void* data)
{
	auto mouseData = static_cast<const Events::MouseState*>(data);

	if (type == EventType::Pressed || type == EventType::Hovered || type == EventType::Dragged || type == EventType::Released)
	{
		DispatchToTopUI(type, mouseData->pos);
	}
}

bool UIManager::IsFullScreenUIActive() const
{
	for (const auto& pair : m_UIObjects)
	{
		if (pair.second->IsVisible() && pair.second->IsFullScreen())
			return true;
	}
	return false;
}

void UIManager::Update(float deltaTime)
{
	for (auto uiObject : m_UIObjects)
	{
		uiObject.second->Update(deltaTime);
	}
}

void UIManager::DispatchToTopUI(EventType type, const POINT& pos)
{
	std::vector<UIObject*> sortedUI;
	sortedUI.reserve(m_UIObjects.size());
	for (auto& pair : m_UIObjects)
		sortedUI.push_back(pair.second.get());

	std::sort(sortedUI.begin(), sortedUI.end(), [](UIObject* a, UIObject* b) {
		return a->GetZOrder() > b->GetZOrder();
		});

	bool fullScreenUIActive = false;
	int fullScreenZ = -1;

	// 전체화면 UI 있는지, zOrder 확인
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
			continue; // 전체화면 UI 아래 UI는 무시

		if (!ui->HitCheck(pos))
			continue;

		switch (type)
		{
		case EventType::Hovered:
			for (auto btn : ui->GetComponents<UIButtonComponent>())
			{
				btn->OnEvent(type, &pos);
			}
		case EventType::Pressed:
		case EventType::Released:
			for (auto btn : ui->GetComponents<UIButtonComponent>())
			{
				btn->OnEvent(type, &pos);
			}
			for (auto slider : ui->GetComponents<UISliderComponent>())
			{
				slider->OnEvent(type, &pos);
			}
			break;
		case EventType::Moved:
			break;
		case EventType::Dragged:
			for (auto slider : ui->GetComponents<UISliderComponent>())
			{
				slider->OnEvent(type, &pos);
			}
			break;
		default:
			break;
		}
	}
}

void UIManager::Render(std::vector<UIRenderInfo>& uiRenderInfo, std::vector<UITextInfo>& uiTextInfo)
{
	for (auto uiObject : m_UIObjects)
	{
		uiObject.second->Render(uiRenderInfo);
		uiObject.second->Render(uiTextInfo);
	}
}