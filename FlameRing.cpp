#include "FlameRing.h"

using namespace std;

FlameRing::FlameRing(unordered_map<IMGEnum, HBITMAP>& hBitmap, unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& winRect, int zLeft, int zRight, int startx, int starty)
{
	bmwidth = bitmapInfo[IMGEnum::ENEMY_B].bmWidth;
	LeftHalfPos = { startx,starty };
	RightHalfPos = { startx+bitmapInfo[IMGEnum::ENEMY_B].bmWidth, starty };
	
	leftHalf = new FlameRingRenderer(hBitmap[IMGEnum::ENEMY_B], bitmapInfo[IMGEnum::ENEMY_B], LeftHalfPos, winRect, zLeft);
	rightHalf = new FlameRingRenderer(hBitmap[IMGEnum::ENEMY_F], bitmapInfo[IMGEnum::ENEMY_F], RightHalfPos, winRect, zRight);
	
	Colider::Tag = COL_TAG_OBSTACLE;
	ringWidth = bitmapInfo[IMGEnum::ENEMY_B].bmWidth + bitmapInfo[IMGEnum::ENEMY_F].bmWidth;
	int ringHeight = bitmapInfo[IMGEnum::ENEMY_B].bmHeight;

	SetRectColider(startx + (int)(ringWidth * 0.25), starty + (int)(ringHeight * 0.9), startx + (int)(ringWidth * 0.75), starty + ringHeight);
	//vertexInfo.push_back({ startx + (int)(ringWidth * 0.25),starty + (int)(ringHeight * 0.9) });
	//vertexInfo.push_back({ startx + (int)(ringWidth * 0.75),starty + (int)(ringHeight * 0.9) });
	//vertexInfo.push_back({ startx + (int)(ringWidth * 0.75),starty + ringHeight });
	//vertexInfo.push_back({ startx + (int)(ringWidth * 0.25),starty + ringHeight });
}

void FlameRing::Update()
{
	if (LeftHalfPos.x < -20)
	{
		//ReturnToGenerationPoint();
		MoveTo(generationPoint);
		return;
	}

	LeftHalfPos.x -= velocity * getDeltaTime();
	RightHalfPos.x -= velocity * getDeltaTime();

	for (int i = 0; i < vertexInfo.size(); i++)
	{
		vertexInfo[i].x -= velocity * getDeltaTime();
	}
}

FlameRing::~FlameRing()
{
	delete leftHalf;
	delete rightHalf;
}

void FlameRing::addRenderer(vector<Renderer*>& rendVec)
{
	rendVec.push_back(leftHalf);
	rendVec.push_back(rightHalf);
}

//void FlameRing::ReturnToGenerationPoint()
//{
//	LeftHalfPos.x = generationPoint;
//	RightHalfPos.x = generationPoint + bmwidth;
//	vertexInfo[0].x = generationPoint + ringWidth * 0.25;
//	vertexInfo[1].x = generationPoint + ringWidth * 0.75;
//	vertexInfo[2].x = generationPoint + ringWidth * 0.75;
//	vertexInfo[3].x = generationPoint + ringWidth * 0.25;
//}

void FlameRing::MoveTo(int xpos)
{
	LeftHalfPos.x = xpos;
	RightHalfPos.x = xpos + bmwidth;
	vertexInfo[0].x = xpos + ringWidth * 0.25;
	vertexInfo[1].x = xpos + ringWidth * 0.75;
	vertexInfo[2].x = xpos + ringWidth * 0.75;
	vertexInfo[3].x = xpos + ringWidth * 0.25;
}

int* FlameRing::getXpos()
{
	return &LeftHalfPos.x;
}