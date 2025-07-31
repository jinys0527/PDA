#include "Obstacle.h"
#include "BoxColliderComponent.h"
#include "SpriteRenderer.h"

Obstacle::Obstacle(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	AddComponent<BoxColliderComponent>();
	AddComponent<SpriteRenderer>();
}