#include "FlamePot.h"

using namespace std;

FlamePot::FlamePot(unordered_map<IMGEnum, HBITMAP>& hBitmap, unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& _winRect, int _zidx, int startx, int starty)
	: winRect(_winRect)
{
	this->startx = startx;
	this->starty = starty;
	Renderer::zIndex = _zidx;

	cntFrame = 0;

	normal = &hBitmap[IMGEnum::FRONT];
	normal2 = &hBitmap[IMGEnum::FRONT2];
	infoNormal = &bitmapInfo[IMGEnum::FRONT];
	infoNormal2 = &bitmapInfo[IMGEnum::FRONT2];
	int width = infoNormal->bmWidth;
	int height = infoNormal->bmHeight;

	Colider::Tag = COL_TAG_OBSTACLE;
	SetRectColider(startx + coliderDx, starty + coliderDy, startx + width - coliderDx, starty + height);
	//vertexInfo.push_back({ startx+coliderDx,starty+coliderDy });
	//vertexInfo.push_back({ startx+width- coliderDx,starty+ coliderDy });
	//vertexInfo.push_back({ startx + width- coliderDx,starty + height });
	//vertexInfo.push_back({ startx+ coliderDx,starty+height });
}

FlamePot::~FlamePot(){}

void FlamePot::Render(HDC hdc, int CameraX)
{
	int RightEnd = startx + infoNormal->bmWidth;
	if (RightEnd - CameraX < 0 || startx - CameraX > winRect.right)
	{
		return;
	}

	if (cntFrame > AnimFrameCut)
	{
		SelectObject(getMemDC(), *normal2);
	}
	else
	{
		SelectObject(getMemDC(), *normal);
	}
	TransparentBlt(hdc, startx - CameraX, starty, infoNormal->bmWidth, infoNormal->bmHeight, getMemDC(), 0, 0, infoNormal->bmWidth, infoNormal->bmHeight, RGB(255, 0, 255));
}

void FlamePot::addRenderer(std::vector<Renderer*>& rendVec)
{
	rendVec.push_back(this);
}

void FlamePot::Update()
{
	cntFrame = cntFrame > 2 * AnimFrameCut ? 0 : cntFrame + 1;
}


void FlamePot::Moveto(int xpos)
{
	startx = xpos;
	int width = infoNormal->bmWidth;
	int height = infoNormal->bmHeight;
	SetRectColider(startx + coliderDx, starty + coliderDy, startx + width - coliderDx, starty + height);
}

int* FlamePot::getXpos()
{
	return &startx;
}