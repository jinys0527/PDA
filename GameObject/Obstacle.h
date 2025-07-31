#pragma once
#include "GameObject.h"

class BoxColliderComponent;
class SpriteRenderer;

class Obstacle : public GameObject
{
public:
	Obstacle(EventDispatcher& eventDispatcher);
	virtual ~Obstacle() = default;


private:
	BoxColliderComponent* m_Collider;
	SpriteRenderer* m_Sprite;
};

