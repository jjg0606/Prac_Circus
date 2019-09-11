#pragma once
#include "Vector2D.h"
#include <vector>
#include <Windows.h>
#include "EnumColTag.h"

class Colider
{	
	// original
	virtual std::vector<Vector2D<int>>& getVertexInfo();
	virtual bool getMinMax(int& xmin, int& xmax, int& ymin, int& ymax);
	virtual bool MinMaxTest(Colider& dest);
	virtual bool InclusionTest(Colider& dest);
protected:
	std::vector<Vector2D<int>> vertexInfo;
	void SetRectColider(int xleft, int ytop, int xright, int ybottom);
public:

	virtual void DrawColider(HDC hdc, int CameraX);
	int Tag;
	virtual bool isCollide(Colider& dest);
	virtual void OnCollision(int destTag) {};
	virtual ~Colider() {};
};
