#pragma once
#include "Renderer.h"
#include "Vector2D.h"

class FlameRingRenderer
	: virtual public Renderer
{
private:
	RECT& winRect;
	HBITMAP& BitMap;
	BITMAP& inBitMap;
	Vector2D<int>& position;
public:
	///*int zIndex;
	void Render(HDC hdc, int CameraX) override;
	FlameRingRenderer(HBITMAP& _BitMap, BITMAP& _inBitMap, Vector2D<int>& _position,RECT& winRect, int zIndex);
};