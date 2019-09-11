#include "BackDecoPattern.h"
#include "ProgramCore.h"

using namespace std;

BackDecoPattern::BackDecoPattern(unordered_map<IMGEnum, HBITMAP>& hBitmap, unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& _winRect, int _zIndex, int _startx, int _starty)
	: winRect(_winRect), startx(_startx), starty(_starty)
{
	Renderer::zIndex = _zIndex;
	bitmapAnim = &hBitmap[IMGEnum::BACK_NORMAL2];
	bitmapNormal = &hBitmap[IMGEnum::BACK_NORMAL];

	bitmapVec.emplace_back(&hBitmap[IMGEnum::BACK_NORMAL]);
	bitmapVec.emplace_back(&hBitmap[IMGEnum::BACK_NORMAL]);
	bitmapVec.emplace_back(&hBitmap[IMGEnum::BACK_NORMAL]);
	bitmapVec.emplace_back(&hBitmap[IMGEnum::BACK_NORMAL]);
	bitmapVec.emplace_back(&hBitmap[IMGEnum::BACK_NORMAL]);
	bitmapVec.emplace_back(&hBitmap[IMGEnum::BACK_NORMAL]);
	bitmapVec.emplace_back(&hBitmap[IMGEnum::BACK_NORMAL]);
	bitmapVec.emplace_back(&hBitmap[IMGEnum::BACK_NORMAL]);
	bitmapVec.emplace_back(&hBitmap[IMGEnum::BACK_DECO]);

	infoVec.emplace_back(&bitmapInfo[IMGEnum::BACK_NORMAL]);
	infoVec.emplace_back(&bitmapInfo[IMGEnum::BACK_NORMAL]);
	infoVec.emplace_back(&bitmapInfo[IMGEnum::BACK_NORMAL]);
	infoVec.emplace_back(&bitmapInfo[IMGEnum::BACK_NORMAL]);
	infoVec.emplace_back(&bitmapInfo[IMGEnum::BACK_NORMAL]);
	infoVec.emplace_back(&bitmapInfo[IMGEnum::BACK_NORMAL]);
	infoVec.emplace_back(&bitmapInfo[IMGEnum::BACK_NORMAL]);
	infoVec.emplace_back(&bitmapInfo[IMGEnum::BACK_NORMAL]);
	infoVec.emplace_back(&bitmapInfo[IMGEnum::BACK_DECO]);
}

void BackDecoPattern::Start()
{
	oneCycleWidth = 0;
	for (int i = 0; i < infoVec.size(); i++)
	{
		oneCycleWidth += infoVec[i]->bmWidth;
	}
}

void BackDecoPattern::Update()
{

}

void BackDecoPattern::Render(HDC hdc, int CameraX)
{

	int lastX = (CameraX-startx) % oneCycleWidth;
	lastX *= -1;

	int startIDX = 0;
	
	for (int i = 0; i < infoVec.size(); i++)
	{
		int nextX = lastX + infoVec[i]->bmWidth;
		if (nextX >= 0)
		{
			startIDX = i;
			break;
		}
		lastX = nextX;
	}

	if (*SceneState == CircusState::PLAYER_WIN)
	{
		RenderWinState(hdc, lastX, startIDX);
	}
	else
	{
		RenderPlayingState(hdc, lastX, startIDX);
	}
}

void BackDecoPattern::RenderPlayingState(HDC hdc, int lastX, int startIDX)
{
	while (lastX < winRect.right)
	{
		for (int i = startIDX; i < bitmapVec.size(); i++)
		{
			SelectObject(getMemDC(), (*bitmapVec[i]));
			TransparentBlt(hdc, lastX, starty, infoVec[i]->bmWidth, infoVec[i]->bmHeight, getMemDC(), 0, 0, infoVec[i]->bmWidth, infoVec[i]->bmHeight, RGB(255, 0, 255));

			lastX += infoVec[i]->bmWidth;
			if (lastX >= winRect.right)
			{
				break;
			}
		}
		startIDX = 0;
	}
}

void BackDecoPattern::RenderWinState(HDC hdc, int lastX, int startIDX)
{
	cntAnim = cntAnim > 2 * AnimFrame ? 0 : cntAnim + 1;

	while (lastX < winRect.right)
	{
		for (int i = startIDX; i < bitmapVec.size(); i++)
		{
			if (bitmapVec[i] == bitmapNormal && cntAnim > AnimFrame)
			{
				SelectObject(getMemDC(), *bitmapAnim);
			}
			else
			{
				SelectObject(getMemDC(), (*bitmapVec[i]));
			}
			TransparentBlt(hdc, lastX, starty, infoVec[i]->bmWidth, infoVec[i]->bmHeight, getMemDC(), 0, 0, infoVec[i]->bmWidth, infoVec[i]->bmHeight, RGB(255, 0, 255));

			lastX += infoVec[i]->bmWidth;
			if (lastX >= winRect.right)
			{
				break;
			}
		}
		startIDX = 0;
	}
}

BackDecoPattern::~BackDecoPattern()
{

}


void BackDecoPattern::addRenderer(vector<Renderer*>& rendVec)
{
	rendVec.push_back(this);
}

void BackDecoPattern::SetSceneStatePointer(CircusState* _state)
{
	this->SceneState = _state;
}