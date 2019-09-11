#pragma once

#include "GameObject.h"
#include "Renderer.h"
#include "IMGEnum.h"
#include "Collider.h"
#include <unordered_map>

class EndTrampoline
	: virtual public GameObject, virtual public Renderer, virtual public Colider
{
	HBITMAP* end;
	BITMAP* infoEnd;
	int startx;
	int starty;
	RECT& winRect;
public:
	//int Tag;
	//int zIndex;
	//std::vector<Vector2D<int>> vertexInfo;
	void addRenderer(std::vector<Renderer*>& rendVec) override;
	void Render(HDC hdc, int CameraX) override;
	//void Update() override;
	EndTrampoline(std::unordered_map<IMGEnum, HBITMAP>& hBitmap, std::unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& winRect, int _zidx, int startx, int starty);
};