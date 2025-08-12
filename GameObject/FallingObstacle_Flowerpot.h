#pragma once
#include "Obstacle.h"
#include "SpriteRenderer.h"
#include "AnimationComponent.h"

class AssetManager;

class FallingObstacle_Flowerpot : public Obstacle
{
public:
	FallingObstacle_Flowerpot(EventDispatcher& eventDispatcher) : Obstacle(eventDispatcher)
	{
		m_Sprite = AddComponent<SpriteRenderer>();
		m_Anim = AddComponent<AnimationComponent>();
	}

	void SetAssetManager(AssetManager* assetManager)
	{
		m_AssetManager = assetManager;
	}
	void Start(AssetManager* assetManager);
	

	virtual ~FallingObstacle_Flowerpot() = default;
private:
	AssetManager* m_AssetManager;
	AnimationComponent* m_Anim;
};

