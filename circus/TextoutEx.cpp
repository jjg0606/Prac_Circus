#include "TextoutEx.h"
#include "ProgramCore.h"

void TextoutEx::Init()
{
	GetClientRect(ProgramCore::instance.getHWND(), &window_rt);

	HDC gdc = GetDC(ProgramCore::instance.getHWND());

	backBuffer = CreateCompatibleDC(gdc);
	drawBitmap = CreateCompatibleBitmap(gdc, window_rt.right, window_rt.bottom);
	oldbitmap = (HBITMAP)SelectObject(backBuffer, drawBitmap);

	memDC = CreateCompatibleDC(backBuffer);
	//hosbitmap = (HBITMAP)LoadImage(NULL, L"0.bmp",IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	//hosbitmap = LoadBitmap(ProgramCore::instance.getGinst(),MAKEINTRESOURCE(IDB_BITMAP1));
	hosbitmap = (HBITMAP)LoadImage(NULL, L"hos2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//SelectObject(memDC, hosbitmap);

	GetObject(hosbitmap, sizeof(BITMAP), &hosbitmapInfo);

	ReleaseDC(ProgramCore::instance.getHWND(), gdc);
	ProgramCore::instance.SetUpdateIntersec(0);
	
}

void TextoutEx::Release()
{
	SelectObject(backBuffer, oldbitmap);
	DeleteObject(drawBitmap);
	DeleteObject(hosbitmap);
}

void TextoutEx::DrawScreen(HDC hdc)
{
	GetClientRect(ProgramCore::instance.getHWND(), &window_rt);
	FillRect(backBuffer, &window_rt, GetSysColorBrush(COLOR_WINDOW));	
	// draw transparently
	SelectObject(memDC, hosbitmap);
	TransparentBlt(backBuffer, mouseX - hosbitmapInfo.bmWidth / 2, mouseY - hosbitmapInfo.bmHeight / 2, hosbitmapInfo.bmWidth, hosbitmapInfo.bmHeight, memDC, 0, 0, hosbitmapInfo.bmWidth, hosbitmapInfo.bmHeight, RGB(250, 0, 250));
	BitBlt(hdc, 0, 0, window_rt.right, window_rt.bottom, backBuffer, 0, 0, SRCCOPY);
}

void TextoutEx::GetMouseMove(int x, int y)
{
	this->mouseX = x;
	this->mouseY = y;
}

void TextoutEx::Update()
{
	ProgramCore::instance.Invalidate();
}