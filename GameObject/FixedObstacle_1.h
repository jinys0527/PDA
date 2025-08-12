#pragma once
#include "Obstacle.h"
#include "SpriteRenderer.h"

class AssetManager;

class FixedObstacle_1 : public Obstacle
{
public:
	FixedObstacle_1(EventDispatcher& eventDispatcher) : Obstacle(eventDispatcher)
	{
		m_Sprite = AddComponent<SpriteRenderer>();
	}
	virtual ~FixedObstacle_1() = default;

	void SetAssetManager(AssetManager* assetManager)
	{
		m_AssetManager = assetManager;
	}

	void Start(AssetManager* assetManager);
private:
	AssetManager* m_AssetManager;
};

