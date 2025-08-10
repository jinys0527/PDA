#pragma once
#include "SimpleMathHelper.h"
#include <windows.h>

inline bool IsPointInUIRect(
	const Math::Vector2F& position,   // RectTransform ��ġ (pivot ���� ��)
	const Math::Vector2F& size,       // ũ��
	const D2D1_POINT_2F& pivot,      // 0~1 pivot
	const POINT& mousePos)             // �˻��� ��ǥ (��ũ�� �Ǵ� UI ��ǥ��)
{
	Math::Vector2F topLeft = position - Math::Vector2F(size.x * pivot.x, size.y * pivot.y);

	return (mousePos.x >= topLeft.x && mousePos.x <= (topLeft.x + size.x) &&
		mousePos.y >= topLeft.y && mousePos.y <= (topLeft.y + size.y));
}