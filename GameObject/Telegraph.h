#pragma once
#include "Obstacle.h"

class Telegraph : public Obstacle
{
public:
	Telegraph(EventDispatcher& eventDispatcher);

	void Update(float deltaTime) override;

	void SetActive();
	void SetInactive();

	void SetColliderActive();

private:
	float m_Opacity = 0.f;
	float m_FadeSpeed = 5.0f;
	float m_Time = 0.f;
	bool m_IsWaving = false;
};
