#include "MiterMark.h"

using namespace std;

MiterMark::MiterMark(std::unordered_map<IMGEnum, HBITMAP>& hBitmap, std::unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& winRect, int _zidx, int startx, int starty, int miter)
	:winRect(winRect)
{
	mark = &hBitmap[IMGEnum::MITER];
	infoMark = &bitmapInfo[IMGEnum::MITER];

	this->startx = startx;
	this->starty = starty;
	Renderer::zIndex = _zidx;

	if (miter > 0)
	{
		wsprintf(miterText, TEXT("%d"), miter);		
	}
	else
	{
		wsprintf(miterText, TEXT("GOAL"));		
	}
	miterTextLength = lstrlen(miterText);
	
}

void MiterMark::addRenderer(vector<Renderer*>& rendVec)
{
	rendVec.push_back(this);
}

void MiterMark::Render(HDC hdc, int CameraX)
{
	int RightEnd = startx + infoMark->bmWidth;
	if (RightEnd - CameraX < 0 || startx - CameraX > winRect.right)
	{
		return;
	}

	SelectObject(getMemDC(), *mark);
	TransparentBlt(hdc, startx - CameraX, starty, infoMark->bmWidth, infoMark->bmHeight, getMemDC(), 0, 0, infoMark->bmWidth, infoMark->bmHeight, RGB(255, 0, 255));

	TextOut(hdc, startx+markDx-CameraX, starty+markDy, miterText, miterTextLength);
}