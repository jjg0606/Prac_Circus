#include "FlameRingRenderer.h"

FlameRingRenderer::FlameRingRenderer(HBITMAP& _BitMap, BITMAP& _inBitMap, Vector2D<int>& _position, RECT& _winRect, int _zIndex)
	: BitMap(_BitMap), inBitMap(_inBitMap), position(_position), winRect(_winRect)
{
	zIndex = _zIndex;
}

void FlameRingRenderer::Render(HDC hdc, int CameraX)
{
	int RightEnd = position.x + inBitMap.bmWidth;
	if (position.x - CameraX > winRect.right || RightEnd - CameraX < 0)
	{
		return;
	}

	SelectObject(getMemDC(), BitMap);
	TransparentBlt(hdc, position.x-CameraX, position.y, inBitMap.bmWidth, inBitMap.bmHeight, getMemDC(), 0, 0, inBitMap.bmWidth, inBitMap.bmHeight, RGB(255, 0, 255));
}