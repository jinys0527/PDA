#pragma once

#include "GameObject.h"

class Background : public GameObject
{
public:
	Background() = default;
	Background(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher) 
	{
		m_moveSpeed = 1000.0f;
	}

	void SetMoveSpeed(float moveSpeed) { m_moveSpeed = moveSpeed; }

	void ToggleScroll() { m_isScroll = !m_isScroll; }
	void Update(float deltaTime) override;
	void FixedUpdate() override;
private:
	void Scroll(float deltaTime);
private:
	bool m_isScroll = true;
	float m_moveSpeed;
};

