#pragma once
#include "GameObject.h"
#include "GraffitiComponent.h"

class GraffitiObject : public GameObject
{
public:
	GraffitiObject(EventDispatcher& eventDispatcher);
	virtual ~GraffitiObject() = default;

	void Render(std::vector<RenderInfo>& renderInfo) override;

private:
	GraffitiComponent* m_GraffitiComponent;
};

