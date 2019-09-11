#include "MiddleObstacle.h"

MiddleObstacle::MiddleObstacle(int* following, int left, int top, int right, int bottom)
{
	followingx = following;
	cntAfterColide = 0.0f;
	Tag = COL_TAG_MIDDLE_OBSTACLE;
	SetRectColider(left, top, right, bottom);
}

void MiddleObstacle::Update()
{
	cntAfterColide -= getDeltaTime();
	if (cntAfterColide < 0)
	{
		cntAfterColide = 0.0f;
		Tag = COL_TAG_MIDDLE_OBSTACLE;
	}

	int dx = (*followingx) - vertexInfo[0].x;
	for (int i = 0; i < vertexInfo.size(); i++)
	{
		vertexInfo[i].x += dx;
	}
}

void MiddleObstacle::OnCollision(int destTag)
{
	cntAfterColide = 2.0f;
	Tag = COL_TAG_NONE;
}