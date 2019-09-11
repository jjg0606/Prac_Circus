#pragma once

#include "GameObject.h"
#include "IMGEnum.h"
#include <unordered_map>

class Floor
	: virtual public GameObject, virtual public Renderer
{
	HBITMAP& bitmap;
	BITMAP& bitmapinfo;
	int startx;
	int starty;
	//int zIndex;
	RECT& winRect;
public:
	void Start() override;
	void Update() override;
	void Render(HDC hdc, int CameraX) override;
	~Floor();
	void addRenderer(std::vector<Renderer*>& rendVec) override;
	Floor(HBITMAP& bitmap, BITMAP& bitmapinfo,RECT& winRect,int zIndex, int startx, int starty);
	Floor(std::unordered_map<IMGEnum, HBITMAP>& hBitmap, std::unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& winRect, int zIndex, int startx, int starty);
};