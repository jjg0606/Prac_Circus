#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "IMGEnum.h"
#include <unordered_map>

class MiterMark
	: virtual public GameObject, virtual public Renderer
{
	wchar_t miterText[10];
	int miterTextLength;

	HBITMAP* mark;
	BITMAP* infoMark;

	static const int markDx = 20;
	static const int markDy = 7;

	int startx;
	int starty;
	RECT& winRect;
public:
	void addRenderer(std::vector<Renderer*>& rendVec) override;
	void Render(HDC hdc, int CameraX) override;
	MiterMark(std::unordered_map<IMGEnum, HBITMAP>& hBitmap, std::unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& winRect, int _zidx, int startx, int starty, int miter);
};