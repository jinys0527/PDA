#pragma once

#include "GameObject.h"

class Background : public GameObject
{
public:
	Background() = default;
	Background(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher) 
	{
		m_moveSpeed = -5.0f;
	}

	void ToggleScroll() { m_isScroll = !m_isScroll; }
	void Update(float deltaTime) override;
private:
	void Scroll(float deltaTime);
	void SetMoveSpeed(float moveSpeed) { m_moveSpeed = moveSpeed; }
private:
	bool m_isScroll = true;
	float m_moveSpeed;
};

