#pragma once
//#include <Windows.h>
#include "Renderer.h"
#include <vector>

class GameObject
{
protected:
	bool GetKey(WPARAM keyName);
	float getDeltaTime();
public:	
	virtual void Start() {};
	virtual void Update() {};
	virtual ~GameObject() {};
	//virtual void Render(HDC hdc, int CameraX) {};
	virtual void addRenderer(std::vector<Renderer*>& rendVec) {};
};