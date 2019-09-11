#include "PlayerAnimRender.h"
#include "ProgramCore.h"

PlayerAnimRender::PlayerAnimRender(std::unordered_map<IMGEnum, HBITMAP>& hBitmap, std::unordered_map<IMGEnum, BITMAP>& bitmapInfo)
{
	PlayerIdle = &hBitmap[IMGEnum::PLAYER0];
	PlayerMove = &hBitmap[IMGEnum::PLAYER1];
	PlayerJump = &hBitmap[IMGEnum::PLAYER2];
	PlayerDie = &hBitmap[IMGEnum::DIE];
	PlayerWin1 = &hBitmap[IMGEnum::WIN];
	PlayerWin2 = &hBitmap[IMGEnum::WIN2];
	inPlayerIdle = &bitmapInfo[IMGEnum::PLAYER0];
	inPlayerMove = &bitmapInfo[IMGEnum::PLAYER1];
	inPlayerJump = &bitmapInfo[IMGEnum::PLAYER2];
	inPlayerDie = &bitmapInfo[IMGEnum::DIE];
	inPlayerWin1 = &bitmapInfo[IMGEnum::WIN];
	inPlayerWin2 = &bitmapInfo[IMGEnum::WIN2];
}

void PlayerAnimRender::RenderIdle(HDC hdc, int CameraX, int posx, int posy)
{
	isIdleMotion = false;
	moveFrame = 0;
	const HDC& memDC = ProgramCore::instance.getMemDC();
	SelectObject(memDC, *PlayerIdle);
	TransparentBlt(hdc, posx - CameraX, posy, inPlayerIdle->bmWidth, inPlayerIdle->bmHeight, memDC, 0, 0, inPlayerIdle->bmWidth, inPlayerIdle->bmHeight, RGB(255, 0, 255));
}

void PlayerAnimRender::RenderJump(HDC hdc, int CameraX, int posx, int posy)
{
	isIdleMotion = false;
	moveFrame = 0;
	const HDC& memDC = ProgramCore::instance.getMemDC();
	SelectObject(memDC, *PlayerJump);
	TransparentBlt(hdc, posx - CameraX, posy, inPlayerJump->bmWidth, inPlayerJump->bmHeight, memDC, 0, 0, inPlayerJump->bmWidth, inPlayerIdle->bmHeight, RGB(255, 0, 255));
}

void PlayerAnimRender::RenderMove(HDC hdc, int CameraX, int posx, int posy)
{
	const HDC& memDC = ProgramCore::instance.getMemDC();


	moveFrame++;

	if (moveFrame >= moveAnimFrame)
	{
		isIdleMotion ^= 1;
		moveFrame = 0;
	}

	if (isIdleMotion)
	{
		SelectObject(memDC, *PlayerIdle);
		TransparentBlt(hdc, posx - CameraX, posy, inPlayerIdle->bmWidth, inPlayerIdle->bmHeight, memDC, 0, 0, inPlayerIdle->bmWidth, inPlayerIdle->bmHeight, RGB(255, 0, 255));
	}
	else
	{
		SelectObject(memDC, *PlayerMove);
		TransparentBlt(hdc, posx - CameraX, posy, inPlayerMove->bmWidth, inPlayerMove->bmHeight, memDC, 0, 0, inPlayerMove->bmWidth, inPlayerMove->bmHeight, RGB(255, 0, 255));
	}
}

void PlayerAnimRender::RenderDie(HDC hdc, int CameraX, int posx, int posy)
{
	const HDC& memDC = ProgramCore::instance.getMemDC();
	SelectObject(memDC, *PlayerDie);
	TransparentBlt(hdc, posx - CameraX, posy, inPlayerDie->bmWidth, inPlayerDie->bmHeight, memDC, 0, 0, inPlayerDie->bmWidth, inPlayerDie->bmHeight, RGB(255, 0, 255));
}

void PlayerAnimRender::RenderWin(HDC hdc, int CameraX, int posx, int posy)
{
	const HDC& memDC = ProgramCore::instance.getMemDC();
	cntWinAnim = cntWinAnim > 2 * winAnimFrame ? 0 : cntWinAnim + 1;
	if (cntWinAnim < winAnimFrame)
	{
		SelectObject(memDC, *PlayerWin1);
		TransparentBlt(hdc, posx - CameraX, posy, inPlayerWin1->bmWidth, inPlayerWin1->bmHeight, memDC, 0, 0, inPlayerWin1->bmWidth, inPlayerWin1->bmHeight, RGB(255, 0, 255));
	}
	else
	{		
		SelectObject(memDC, *PlayerWin2);
		TransparentBlt(hdc, posx - CameraX, posy, inPlayerWin2->bmWidth, inPlayerWin2->bmHeight, memDC, 0, 0, inPlayerWin2->bmWidth, inPlayerWin2->bmHeight, RGB(255, 0, 255));
	}
}
