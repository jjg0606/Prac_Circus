#pragma once
#include <Windows.h>
#include "MouseEnum.h"

class Scene
{
public:
	virtual void DrawScreen(HDC hdc) {}
	virtual void GetInput(WPARAM wParam) {}
	//virtual void GetKeyDown(WPARAM wParam) {}
	virtual void Update() {}
	virtual void Release() {}
	virtual void Init() {}
	virtual void GetMouseClick(int x, int y, int E_MOUSE_BTN) {}
	virtual void GetMouseMove(int x, int y) {}
	virtual ~Scene() {}
};