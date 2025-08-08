#pragma once
#include "Object.h"

class RectTransformComponent;

class UIObject : public Object
{
	friend class Scene;
	friend class TestScene;
	friend class TitleScene;
public:
	UIObject(EventDispatcher& eventDispatcher);
	virtual ~UIObject() = default;

	void Render(std::vector<UIRenderInfo>& renderInfo);
	void Render(std::vector<UITextInfo>& textInfo);

protected:
	RectTransformComponent* m_RectTransform;
};

