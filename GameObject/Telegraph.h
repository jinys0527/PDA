#pragma once
#include "Obstacle.h"

class Telegraph : public Obstacle
{
public:
	Telegraph(EventDispatcher& eventDispatcher);

	void Update(float deltaTime) override;

	void SetActive();
	void SetInactive();

	void SetColliderActive(bool active);

	void SetActiveAnimation();

	Math::Vector2F GetInitPos()
	{
		return m_InitPos;
	}

	Math::Vector2F GetCurrPos();

private:
	void SetInactiveAnimation();


	float m_Opacity = 0.f;
	float m_FadeSpeed = 5.0f;
	float m_Time = 0.f;
	bool m_IsWaving = false;
	bool m_IsInitialized = false;
	bool m_IsAnimationPlaying = false;

	Math::Vector2F m_InitPos = { 0,0 };

	Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_WarningTexture;
};
