#include "Floor.h"
#include "ProgramCore.h"
using namespace std;

Floor::Floor(HBITMAP& _bitmap,BITMAP& _bitmapinfo, RECT& _winRect,int _zIndex, int _startx,int _starty)
	: bitmap(_bitmap), bitmapinfo(_bitmapinfo), winRect(_winRect), startx(_startx), starty(_starty)
{
	Renderer::zIndex = _zIndex;
}

Floor::Floor(unordered_map<IMGEnum, HBITMAP>& hBitmap, unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& winRect, int zIndex, int startx, int starty)
	: Floor(hBitmap[IMGEnum::BACK],bitmapInfo[IMGEnum::BACK],winRect,zIndex,startx,starty)
{

}

void Floor::Start()
{

}

void Floor::Update()
{

}

Floor::~Floor()
{

}

void Floor::Render(HDC hdc, int CameraX)
{
	HDC memDC = ProgramCore::instance.getMemDC();
	SelectObject(memDC, bitmap);
	//BitBlt(hdc, startx, starty, winRect.right, winRect.bottom, memDC, 0, 0, SRCCOPY);
	TransparentBlt(hdc, startx, starty, winRect.right, bitmapinfo.bmHeight, memDC, 0, 0, bitmapinfo.bmWidth, bitmapinfo.bmHeight, RGB(255, 0, 255));
}

void Floor::addRenderer(vector<Renderer*>& rendVec)
{
	rendVec.push_back(this);
}