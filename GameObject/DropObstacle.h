#pragma once
#include "Obstacle.h"

class DropObstacle : public Obstacle
{
public:
	DropObstacle(EventDispatcher& eventDispatcher);
	~DropObstacle();

	void Update(float deltaTime) override;
	void Render(std::vector<RenderInfo>& renderInfo) override;

private:
	float m_Z;
	bool m_IsSlide;
	BoxColliderComponent* m_Collider;
	SpriteRenderer* m_Sprite;
};

