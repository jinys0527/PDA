#pragma once
#include "Obstacle.h"
#include "SpriteRenderer.h"
#include "BoxColliderComponent.h"

class AssetManager;

class FallingObstacle_Box : public Obstacle
{
public:
	FallingObstacle_Box(EventDispatcher& eventDispatcher) : Obstacle(eventDispatcher)
	{
		m_Collider->SetSize({ 691.0f, 132.0f });
		m_Sprite = AddComponent<SpriteRenderer>();
	}
	virtual ~FallingObstacle_Box() = default;

	void SetAssetManager(AssetManager* assetManager)
	{
		m_AssetManager = assetManager;
	
	}
	void Start(AssetManager* assetManager);

private:
	AssetManager* m_AssetManager;
};


