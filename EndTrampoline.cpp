#include "EndTrampoline.h"

using namespace std;

EndTrampoline::EndTrampoline(std::unordered_map<IMGEnum, HBITMAP>& hBitmap, std::unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& winRect, int _zidx, int startx, int starty)
	: winRect(winRect)
{
	end = &hBitmap[IMGEnum::END];
	infoEnd = &bitmapInfo[IMGEnum::END];
	this->startx = startx;
	this->starty = starty;
	Renderer::zIndex = _zidx;

	int width = infoEnd->bmWidth;
	int height = infoEnd->bmHeight;

	vertexInfo.push_back({ startx,starty });
	vertexInfo.push_back({ startx + width,starty });
	vertexInfo.push_back({ startx + width,starty + height });
	vertexInfo.push_back({ startx ,starty + height });
	Colider::Tag = COL_TAG_END;
}	

void EndTrampoline::addRenderer(vector<Renderer*>& rendVec)
{
	rendVec.push_back(this);
}

void EndTrampoline::Render(HDC hdc, int CameraX)
{
	int RightEnd = startx + infoEnd->bmWidth;
	if (RightEnd - CameraX < 0 || startx - CameraX > winRect.right)
	{
		return;
	}
		
	SelectObject(getMemDC(), *end);
	TransparentBlt(hdc, startx - CameraX, starty, infoEnd->bmWidth, infoEnd->bmHeight, getMemDC(), 0, 0, infoEnd->bmWidth, infoEnd->bmHeight, RGB(255, 0, 255));
}