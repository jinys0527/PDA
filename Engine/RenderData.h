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
	Math::Vector2F parentSize;
	Math::Vector2F anchoredPosition;
	Math::Vector2F sizeDelta;
	Math::Vector2F pivot;
	Anchor anchor;
	D2D1::Matrix3x2F worldMatrix;
	float opacity = 1.0f;
	int layer = 0;
	bool draw = true;
};

struct TextInfo
{
    const wchar_t* text;                // �ʼ�
    Math::Vector2F size;              // ���� ũ��(����, ����)
    D2D1::Matrix3x2F worldMatrix;    // ��ġ �� ��ȯ ���
    D2D1_COLOR_F color = D2D1::ColorF(D2D1::ColorF::Black);
    float opacity = 1.0f;
    int layer = 0;
    std::wstring font = L"���� ���";
    float fontSize = 16.0f;

    // ���� ����, ���� �ɼ�
    //DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL;
    //DWRITE_FONT_STYLE fontStyle = DWRITE_FONT_STYLE_NORMAL;
    //DWRITE_TEXT_ALIGNMENT textAlignment = DWRITE_TEXT_ALIGNMENT_LEADING;
    //DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment = DWRITE_PARAGRAPH_ALIGNMENT_NEAR;

    //float maxWidth = 1000.0f;         //�ؽ�Ʈ ���̾ƿ�
    //float maxHeight = 1000.0f;        //�ؽ�Ʈ ���̾ƿ�
    //bool wrapText = false;            //�ٹٲ�
};