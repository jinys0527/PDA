#pragma once
#include "Object.h"
#include <windows.h>

class RectTransformComponent;
class UIButtonComponent;
class UISliderComponent;

class UIObject : public Object
{
	friend class UIManager;
	friend class Scene;
	friend class TitleScene;
	friend class InGameUITestScene;
	friend class BossScene;
public:
	UIObject(EventDispatcher& eventDispatcher);
	virtual ~UIObject() = default;

	void Render(std::vector<UIRenderInfo>& renderInfo);
	void Render(std::vector<UITextInfo>& textInfo);

	void SetZOrder(int zOrder) { m_ZOrder = zOrder; }
	int GetZOrder() const { return m_ZOrder; }

	bool HitCheck(const POINT& pos);
	
	void SetIsFullScreen(bool isFullScreen) { m_IsFullScreen = isFullScreen; }
	bool IsFullScreen();

	void SetIsVisible(bool isVisible) 
	{
		m_IsVisible = isVisible;

		//// �ڽĵ����׵� ��� ȣ���ؼ� �����ϰ� ����
		//for (auto& child : m_RectTransform->GetChild())
		//{
		//	if (child)
		//	{
		//		auto owner = dynamic_cast<UIObject*>(child->GetOwner());
		//		if (owner)
		//		{
		//			owner->SetIsVisible(isVisible);
		//		}
		//	}
		//}
	}
	bool IsVisible();

	// UI ������Ʈ ������Ʈ �߰�/���� �� �÷��� ���� ���� (UIObject ����)
	void UpdateInteractableFlags();
	

protected:
	// UI ������Ʈ�� ������Ʈ ���� ���� �÷��� (UIObject Ŭ������ �߰�)
	bool hasButton = false;
	bool hasSlider = false;

	RectTransformComponent* m_RectTransform;
	int m_ZOrder = 0;
	bool m_IsFullScreen = false;
	bool m_IsVisible = true;
};

