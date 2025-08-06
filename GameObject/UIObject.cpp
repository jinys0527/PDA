#include "UIObject.h"
#include "RectTransformComponent.h"
#include "UIImageComponent.h"

UIObject::UIObject(EventDispatcher& eventDispatcher) : Object(eventDispatcher)
{
	m_RectTransform = AddComponent<RectTransformComponent>();
}

void UIObject::Render(std::vector<UIRenderInfo>& renderInfo)
{
	auto uiImage = GetComponent<UIImageComponent>();

	if (uiImage)
	{
		UIRenderInfo info;
		info.anchor = Anchor{ {0.0f, 0.0f}, {0.0f, 0.0f} }; // (0,0)-(0,0) ������
		info.anchoredPosition = m_RectTransform->GetPosition();
		info.sizeDelta = { 0, 0 };
		info.parentSize = { 0, 0 };
		info.pivot = m_RectTransform->GetPivot();
		// Opacity ����
		info.opacity = uiImage->GetOpacity();
		renderInfo.emplace_back(info);
	}
	else
	{
		return;
	}
}