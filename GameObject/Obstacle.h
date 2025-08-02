#pragma once
#include "GameObject.h"

class BoxColliderComponent;
class SpriteRenderer;

class Obstacle : public GameObject
{
public:
	Obstacle(EventDispatcher& eventDispatcher);
	virtual ~Obstacle() = default;
	
	void SetZ(float value) { m_Z = value; }
	float GetZ() { return m_Z; }
private:
	float m_Z;
	BoxColliderComponent* m_Collider;
	SpriteRenderer* m_Sprite;
};

