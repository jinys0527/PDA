#pragma once
#include "Obstacle.h"
#include "SpriteRenderer.h"
#include "BoxColliderComponent.h"

class AssetManager;

class SlidingObstacle : public Obstacle
{
public:
	SlidingObstacle(EventDispatcher& eventDispatcher) : Obstacle(eventDispatcher)
	{
		m_IsSlide = true;
		m_Collider->SetSize({ 691.0f, 132.0f });
		m_Sprite = AddComponent<SpriteRenderer>();
	}
	virtual ~SlidingObstacle() = default;	
	
	void SetAssetManager(AssetManager* assetManager)
	{
		m_AssetManager = assetManager;
	}

	void Start(AssetManager* assetManager);

private:
	AssetManager* m_AssetManager;
};

