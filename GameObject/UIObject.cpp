#include "UIObject.h"
#include "RectTransformComponent.h"
#include "UIImageComponent.h"
#include "UISliderComponent.h"
#include "UIButtonComponent.h"
#include "UIGridComponent.h"
#include "UITextComponent.h"
#include "UIUtils.h"

UIObject::UIObject(EventDispatcher& eventDispatcher) : Object(eventDispatcher)
{
	m_RectTransform = AddComponent<RectTransformComponent>();
}

void UIObject::Render(std::vector<UIRenderInfo>& renderInfo)
{
	for (auto& image : GetComponents<UIImageComponent>())
	{
		UIRenderInfo info;
		info.bitmap = image->GetTexture();
		info.anchoredPosition = m_RectTransform->GetPosition();
		info.anchor = m_RectTransform->GetAnchor();
		info.sizeDelta = { 0, 0 }; 
		if (m_RectTransform->GetParent())
		{
			auto parentSize = m_RectTransform->GetParent()->GetSize();
			info.parentSize = parentSize;
		}
		else
		{
			auto size = m_RectTransform->GetSize();
			info.parentSize = { size.x, size.y };
		}
		info.pivot = m_RectTransform->GetPivot();
		// Opacity ����
		info.opacity = image->GetOpacity();
		info.srcRect = D2D1_RECT_F{ image->GetUV().left, image->GetUV().top, image->GetUV().right, image->GetUV().bottom };
		renderInfo.emplace_back(info);
	}
	for(auto& slider : GetComponents<UISliderComponent>())
	{
		UIRenderInfo frameInfo;
		auto frameImage = slider->GetFrame()->GetComponent<UIImageComponent>();
		frameInfo.bitmap = frameImage->GetTexture();
		auto frameRect = slider->GetFrame()->GetComponent<RectTransformComponent>();
		frameInfo.anchor = frameRect->GetAnchor();
		frameInfo.anchoredPosition = frameRect->GetPosition();
		frameInfo.sizeDelta = { 0, 0 };
		if (frameRect->GetParent())
		{
			auto parentSize = frameRect->GetParent()->GetSize();
			frameInfo.parentSize = parentSize;
		}
		else
		{
			auto size = frameRect->GetSize();
			frameInfo.parentSize = size;
		}
		frameInfo.pivot = frameRect->GetPivot();
		// Opacity ����
		frameInfo.opacity = frameImage->GetOpacity();
		frameInfo.srcRect = D2D1_RECT_F{ frameImage->GetUV().left, frameImage->GetUV().top, frameImage->GetUV().right, frameImage->GetUV().bottom };
		frameInfo.useSrcRect = true;
		renderInfo.emplace_back(frameInfo);
		
		UIRenderInfo fillInfo;
		auto fillImage = slider->GetFill()->GetComponent<UIImageComponent>();
		fillInfo.bitmap = fillImage->GetTexture();
		auto fillRect = slider->GetFill()->GetComponent<RectTransformComponent>();
		fillInfo.anchor = fillRect->GetAnchor();
		fillInfo.anchoredPosition = fillRect->GetPosition();
		fillInfo.sizeDelta = { 0, 0 };
		if (fillRect->GetParent())
		{
			auto parentSize = fillRect->GetParent()->GetSize();
			fillInfo.parentSize = parentSize;
		}
		else
		{
			auto size = fillRect->GetSize();
			fillInfo.parentSize = size;
		}
		fillInfo.pivot = fillRect->GetPivot();
		// Opacity ����
		fillInfo.opacity = fillImage->GetOpacity();
		fillInfo.srcRect = D2D1_RECT_F{ fillImage->GetUV().left, fillImage->GetUV().top, fillImage->GetUV().right, fillImage->GetUV().bottom };
		fillInfo.useSrcRect = true;
		renderInfo.emplace_back(fillInfo);
	}
	for (auto& grid : GetComponents<UIGridComponent>())
	{
		for (auto item : grid->GetItems())
		{
			for (auto image : item->GetComponents<UIImageComponent>())
			{
				UIRenderInfo info;
				info.bitmap = image->GetTexture();
				auto rect = item->GetComponent<RectTransformComponent>();
				info.anchoredPosition = rect->GetPosition();
				info.anchor = rect->GetAnchor();
				info.sizeDelta = { 0, 0 };
				if (rect->GetParent())
				{
					auto parentSize = rect->GetParent()->GetSize();
					info.parentSize = parentSize;
				}
				else
				{
					auto size = rect->GetSize();
					info.parentSize = { size.x, size.y };
				}
				info.pivot = rect->GetPivot();
				// Opacity ����
				info.opacity = image->GetOpacity();
				info.srcRect = D2D1_RECT_F{ image->GetUV().left, image->GetUV().top, image->GetUV().right, image->GetUV().bottom };
				renderInfo.emplace_back(info);
			}
		}
	}
}

void UIObject::Render(std::vector<UITextInfo>& renderInfo)
{
	for (auto& text : GetComponents<UITextComponent>())
	{
		UITextInfo info;
		info.anchoredPosition = m_RectTransform->GetPosition();
		info.anchor = m_RectTransform->GetAnchor();
		info.sizeDelta = { 0, 0 };
		if (m_RectTransform->GetParent())
		{
			auto parentSize = m_RectTransform->GetParent()->GetSize();
			info.parentSize = parentSize;
		}
		else
		{
			auto size = m_RectTransform->GetSize();
			info.parentSize = { size.x, size.y };
		}
		info.pivot = m_RectTransform->GetPivot();
		// Opacity ����

		info.color = text->GetColor();
		info.fontSize = text->GetFontSize();
		info.text = text->GetText();
		info.textLayout = text->GetTextLayout();
		renderInfo.emplace_back(info);
	}
}

bool UIObject::HitCheck(const POINT& pos)
{
	auto rectTransform = GetComponent<RectTransformComponent>();
	if (!rectTransform) return false;

	auto size = rectTransform->GetSize();
	auto position = rectTransform->GetPosition();
	auto pivot = rectTransform->GetPivot();

	return IsPointInUIRect(position, size, pivot, pos);
}

bool UIObject::IsFullScreen()
{
	return false;
}

bool UIObject::IsVisible()
{
	return false;
}
