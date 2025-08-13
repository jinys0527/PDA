#pragma once
#include <wrl/client.h>
#include <d2d1_1.h>
#include <string>
#include "SimpleMathHelper.h"
#include "RectTransformComponent.h"

struct RenderInfo
{
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap;
	Math::Vector2F size;
	Math::Vector2F pivot;
	Math::Vector2F center;
	D2D1::Matrix3x2F worldMatrix; 
	float opacity = 1.0f;
	int layer = 0;
	bool useSrcRect = false;
	D2D1_RECT_F srcRect = {};
	bool draw = true;
};

struct UIRenderInfo
{
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap;
	Math::Vector2F parentSize;

	Anchor anchor;
	Math::Vector2F anchoredPosition;
	Math::Vector2F sizeDelta;
	D2D1_POINT_2F pivot;

	float opacity = 1.0f;
	int layer = 0;
	bool useSrcRect = false;
	D2D1_RECT_F srcRect = {};
	bool draw = true;
};

struct UITextInfo : public UIRenderInfo
{
	std::wstring text;
	float fontSize = 16.0f;
	D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Black);
	Microsoft::WRL::ComPtr<IDWriteTextLayout> textLayout;
};