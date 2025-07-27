#pragma once
#include <wrl/client.h>
#include <d2d1_1.h>
#include <string>
#include "SimpleMathHelper.h"
#include "RectTransformComponent.h"

struct RenderInfo
{
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap;
	Math::Vector2F position;
	Math::Vector2F size;
	Math::Vector2F parentSize;
	Math::Vector2F anchoredPosition;
	Math::Vector2F sizeDelta;
	Math::Vector2F pivot;
	Anchor anchor;
	Math::Vector2F scale = { 1.0f, 1.0f };
	float rotation = 0.0f;
	float opacity = 1.0f;
	int layer = 0;
};