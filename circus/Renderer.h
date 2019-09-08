#pragma once
#include <Windows.h>

class Renderer
{
protected:
	HDC getMemDC();
public:
	int zIndex;
	virtual void Render(HDC hdc,int CameraX) = 0;

	bool operator<(Renderer& dest)
	{
		return zIndex < dest.zIndex;
	}

	bool operator<(Renderer* dest)
	{
		return zIndex < dest->zIndex;
	}
};