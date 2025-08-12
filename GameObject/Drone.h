#pragma once
#include "GameObject.h"

class AssetManager;
class SpriteRenderer;
class AnimationComponent;

class Drone : public GameObject
{
public:
	Drone(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
	{
		m_Sprite = AddComponent<SpriteRenderer>();
		m_Anim = AddComponent<AnimationComponent>();
	}
	virtual ~Drone() = default;


	void SetAssetManager(AssetManager* assetManager)
	{
		m_AssetManager = assetManager;
	}
	void Start(AssetManager* assetManager);
	
private:
	AssetManager* m_AssetManager;
	SpriteRenderer* m_Sprite;
	AnimationComponent* m_Anim;
};

