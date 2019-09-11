#pragma once

#include "GameObject.h"
#include "IMGEnum.h"
#include <unordered_map>
#include "Player.h"

class UIRenderer
	: virtual public GameObject, virtual public Renderer
{
	std::unordered_map<IMGEnum, HBITMAP>& hBitmap;
	std::unordered_map<IMGEnum, BITMAP>& bitmapInfo;
	Player* playerInstance;
	RECT& winRect;
	// zindex
	HPEN outLinePen;
	HPEN lifePen;
	void DrawOutLine(HDC hdc);
	void DrawScore(HDC hdc);
	wchar_t scoreBuf[50];
	void DrawLife(HDC hdc);
	wchar_t lifeBuf[20];

	void DrawBonusScore(HDC hdc);
	wchar_t bonusScoreBuf[50];
	int BonusScore = 5000;
	float timePassed = 0.0f;
	static const int timeScoreDown = 3;
public:
	void Update() override;
	void addRenderer(std::vector<Renderer*>& rendVec) override;
	UIRenderer(std::unordered_map<IMGEnum, HBITMAP>& hBitmap, std::unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& winRect, int zIndex, Player* playerInst);
	void Render(HDC hdc, int CameraX) override;
	~UIRenderer();
};