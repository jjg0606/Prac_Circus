#pragma once
#include "GameObject.h"
#include "Renderer.h"
#include "IMGEnum.h"
#include "Collider.h"
#include <unordered_map>

class FlamePot
	: virtual public GameObject, virtual public Renderer,virtual public Colider
{
private:
	HBITMAP* normal;
	HBITMAP* normal2;
	BITMAP* infoNormal;
	BITMAP* infoNormal2;
	int startx;
	int starty;
	RECT& winRect;
	static const int coliderDx = 10;
	static const int coliderDy = 5;
	int cntFrame;
	static const int AnimFrameCut = 10;
public:
	//int Tag;
	//int zIndex;
	//std::vector<Vector2D<int>> vertexInfo;
	int* getXpos();
	~FlamePot();
	void addRenderer(std::vector<Renderer*>& rendVec) override;
	void Render(HDC hdc, int CameraX) override;
	void Update() override;
	void Moveto(int xpos);
	FlamePot(std::unordered_map<IMGEnum, HBITMAP>& hBitmap, std::unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& winRect, int _zidx, int startx, int starty);
};