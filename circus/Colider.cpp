#include "Collider.h"
#include <math.h>

using namespace std;

bool Colider::isCollide(Colider& dest)
{
	//if (!MinMaxTest(dest))
	//{
	//	return false;
	//}	
	if (InclusionTest(dest) || dest.InclusionTest(*this))
	{
		return true;
	}
	return false;
}

vector<Vector2D<int>>& Colider::getVertexInfo()
{
	return vertexInfo;
}

bool Colider::getMinMax(int& xmin, int& xmax, int& ymin, int& ymax)
{
	if (vertexInfo.size() == 0)
	{
		return false;
	}

	xmin = vertexInfo[0].x;
	xmax = vertexInfo[0].x;
	ymin = vertexInfo[0].y;
	ymax = vertexInfo[0].y;

	for (int i = 1; i < vertexInfo.size(); i++)
	{
		if (vertexInfo[i].x < xmin)
		{
			xmin = vertexInfo[i].x;
		}
		if (vertexInfo[i].x > xmax)
		{
			xmax = vertexInfo[i].x;
		}
		if (vertexInfo[i].y < ymin)
		{
			ymin = vertexInfo[i].y;
		}
		if (vertexInfo[i].y > ymax)
		{
			ymax = vertexInfo[i].y;
		}
	}

	return true;
}

bool Colider::MinMaxTest(Colider& dest)
{
	int sorXmin, sorXmax, sorYmin, sorYmax;
	if (!getMinMax(sorXmin, sorXmax, sorYmin, sorYmax))
	{
		return false;
	}

	int destXmin, destXmax, destYmin, destYmax;
	if (!dest.getMinMax(destXmin, destXmax, destYmin, destYmax))
	{
		return false;
	}

	if (sorXmax < destXmin || destXmax < sorXmin || sorYmax < destYmin || destYmax < sorYmin)
	{
		return false;
	}

	return true;
}

bool Colider::InclusionTest(Colider& dest)
{
	vector<Vector2D<int>>& destVertex = dest.getVertexInfo();
		
	for(int i=0;i<vertexInfo.size();i++)
	{ 
		float angleSum = 0.0f;
		for (int j = 0; j < destVertex.size(); j++)
		{
			Vector2D<int> v1 = destVertex[j] - vertexInfo[i];
			int second = (j + 1) % destVertex.size();
			Vector2D<int> v2 = destVertex[second] - vertexInfo[i];

			int inpro = v1 * v2;
			float size = sqrtf(v1.x * v1.x + v1.y * v1.y) * sqrtf(v2.x * v2.x + v2.y * v2.y);
			angleSum += acosf(inpro / size);
		}
		if (angleSum > 6.1f)
		{
			return true;
		}
	}
	return false;
}

void Colider::DrawColider(HDC hdc, int CameraX)
{
	for (int i = 0; i < vertexInfo.size(); i++)
	{
		int next = (i + 1) % vertexInfo.size();
		MoveToEx(hdc, vertexInfo[i].x - CameraX, vertexInfo[i].y, NULL);
		LineTo(hdc, vertexInfo[next].x - CameraX, vertexInfo[next].y);
	}
}