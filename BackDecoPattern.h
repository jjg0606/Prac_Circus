#pragma once
#include "GameObject.h"
#include "IMGEnum.h"
#include <unordered_map>
#include <vector>
#include "EnumCircusState.h"

class BackDecoPattern
	: virtual public GameObject, virtual public Renderer
{
	std::vector<HBITMAP*> bitmapVec;
	HBITMAP* bitmapNormal;
	HBITMAP* bitmapAnim;
	std::vector<BITMAP*> infoVec;
	int oneCycleWidth = 0;
	int startx;
	int starty;
	//int zIndex;
	RECT& winRect;
	CircusState* SceneState = nullptr;
	void RenderPlayingState(HDC hdc, int lastX,int startIDX);
	void RenderWinState(HDC hdc, int lastX,int startIDx);
	int cntAnim = 0;
	static const int AnimFrame = 10;
public:
	
	void Start() override;
	void Update() override;
	void addRenderer(std::vector<Renderer*>& rendVec) override;

	void Render(HDC hdc, int CameraX) override;
	~BackDecoPattern();

	BackDecoPattern(std::unordered_map<IMGEnum, HBITMAP>& hBitmap, std::unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& winRect, int zIndex, int startx, int starty);
	void SetSceneStatePointer(CircusState* _state);
};