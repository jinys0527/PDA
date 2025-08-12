#pragma once
#include "Obstacle.h"
#include "SpriteRenderer.h"
#include "BoxColliderComponent.h"

class AssetManager;

class FixedObstacle_2 : public Obstacle
{
public:
	FixedObstacle_2(EventDispatcher& eventDispatcher) : Obstacle(eventDispatcher)
	{		
		m_Sprite = AddComponent<SpriteRenderer>();
		m_Collider->SetSize({ 257.0f, 277.0f });
	}
	virtual ~FixedObstacle_2() = default;

	void SetAssetManager(AssetManager* assetManager)
	{
		m_AssetManager = assetManager;
	}

	void Start(AssetManager* assetManager);
private:
	AssetManager* m_AssetManager;
};

