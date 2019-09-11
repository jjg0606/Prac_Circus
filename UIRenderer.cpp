#include "UIRenderer.h"

using namespace std;

UIRenderer::UIRenderer(unordered_map<IMGEnum, HBITMAP>& hBitmap, unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& winRect, int zIndex, Player* playerInst)
	: hBitmap(hBitmap), bitmapInfo(bitmapInfo), winRect(winRect)
{
	this->playerInstance = playerInst;
	Renderer::zIndex = zIndex;
	outLinePen = CreatePen(PS_DOT, 3, RGB(0, 255, 255));
	lifePen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));

	wsprintf(lifeBuf, TEXT("PLAYER LIFE"));
}

UIRenderer::~UIRenderer()
{
	DeleteObject(outLinePen);
	DeleteObject(lifePen);
}

void UIRenderer::addRenderer(vector<Renderer*>& rendVec)
{
	rendVec.push_back(this);
}

void UIRenderer::Update()
{
	timePassed += getDeltaTime();
	if (timePassed > timeScoreDown)
	{
		timePassed -= timeScoreDown;
		BonusScore = BonusScore >= 100 ? BonusScore-100 : 0;
	}
}

void UIRenderer::Render(HDC hdc, int CameraX)
{
	int oldMode = SetBkMode(hdc, TRANSPARENT);
	DrawOutLine(hdc);
	DrawScore(hdc);
	DrawLife(hdc);
	DrawBonusScore(hdc);
	SetBkMode(hdc, oldMode);
}

void UIRenderer::DrawOutLine(HDC hdc)
{
	HPEN oldPen = (HPEN)SelectObject(hdc, outLinePen);
	MoveToEx(hdc, winRect.right*0.1, winRect.bottom*0.1, NULL);
	LineTo(hdc, winRect.right*0.9, winRect.bottom*0.1);
	LineTo(hdc, winRect.right*0.9, winRect.bottom*0.4);
	LineTo(hdc, winRect.right*0.1, winRect.bottom*0.4);
	LineTo(hdc, winRect.right*0.1, winRect.bottom*0.1);

	SelectObject(hdc, oldPen);	
}

void UIRenderer::DrawScore(HDC hdc)
{
	SetTextColor(hdc, RGB(255, 255, 255));
	wsprintf(scoreBuf, TEXT("PLAYER SCORE : %d"), playerInstance->getScore());
	TextOut(hdc, winRect.right*0.2, winRect.bottom*0.25, scoreBuf, lstrlen(scoreBuf));
	SetTextColor(hdc, RGB(0, 0, 0));
}

void UIRenderer::DrawLife(HDC hdc)
{
	HBITMAP& icon = hBitmap[IMGEnum::ICON];
	BITMAP& info = bitmapInfo[IMGEnum::ICON];

	int life = playerInstance->getLife();
	int startPosX = winRect.right*0.2;
	int startPosY = winRect.bottom*0.35;
	int DX = 30;
	int DY = 30;
	

	HPEN oldPen = (HPEN)SelectObject(hdc, lifePen);
	SetTextColor(hdc, RGB(255, 0, 0));
	TextOut(hdc, startPosX, startPosY, lifeBuf, lstrlen(lifeBuf));
	startPosX += 100;
	SelectObject(getMemDC(), icon);
	for (int i = 0; i < life; i++)
	{
		TransparentBlt(hdc, startPosX, startPosY, DX, DY, getMemDC(), 0, 0, info.bmWidth, info.bmHeight, RGB(255, 0, 255));
		startPosX += DX * 1.3;
		/*MoveToEx(hdc, startPosX, startPosY, NULL);
		LineTo(hdc, startPosX, startPosY + DY);
		startPosX += DX;*/
	}
	SelectObject(hdc, oldPen);
	SetTextColor(hdc, RGB(0, 0, 0));
}

void UIRenderer::DrawBonusScore(HDC hdc)
{
	
	SetTextColor(hdc, RGB(255, 255, 255));
	wsprintf(bonusScoreBuf, TEXT("BONUS SCORE : %d"), BonusScore);
	TextOut(hdc, winRect.right*0.5, winRect.bottom*0.25, bonusScoreBuf, lstrlen(bonusScoreBuf));
	SetTextColor(hdc, RGB(0, 0, 0));
}