#include "Telegraph.h"
#include "BoxColliderComponent.h"

Telegraph::Telegraph(EventDispatcher& eventDispatcher) : GameObject(eventDispatcher)
{
	auto box = AddComponent<BoxColliderComponent>();
	box->SetSize({ 100.f, 100.f });
	box->Start();
}