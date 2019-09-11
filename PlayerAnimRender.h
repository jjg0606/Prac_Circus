#pragma once
#include <Windows.h>
#include "IMGEnum.h"
#include <unordered_map>

class PlayerAnimRender
{
private:
	HBITMAP* PlayerIdle;
	HBITMAP* PlayerMove;
	HBITMAP* PlayerJump;
	HBITMAP* PlayerDie;
	HBITMAP* PlayerWin1;
	HBITMAP* PlayerWin2;
	BITMAP* inPlayerIdle;
	BITMAP* inPlayerMove;
	BITMAP* inPlayerJump;
	BITMAP* inPlayerDie;
	BITMAP* inPlayerWin1;
	BITMAP* inPlayerWin2;

	int moveFrame = 0;
	bool isIdleMotion = true;

	static const int moveAnimFrame = 10;

	int cntWinAnim = 0;
	static const int winAnimFrame = 15;
public:
	void RenderIdle(HDC hdc, int CameraX, int posx,int posy);
	void RenderJump(HDC hdc, int CameraX, int posx,int posy);
	void RenderMove(HDC hdc, int CameraX, int posx,int posy);
	void RenderDie(HDC hdc, int CameraX, int posx, int posy);
	void RenderWin(HDC hdc, int CameraX, int posx, int posy);
	PlayerAnimRender(std::unordered_map<IMGEnum, HBITMAP>& hBitmap, std::unordered_map<IMGEnum, BITMAP>& bitmapInfo);
};