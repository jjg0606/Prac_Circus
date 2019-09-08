#pragma once
#include "Scene.h"

class TextoutEx
	: virtual public Scene
{
private:
	int mouseX;
	int mouseY;
	HBITMAP hosbitmap;
	BITMAP hosbitmapInfo;
	HDC memDC;
	HDC backBuffer;

	HBITMAP oldbitmap;
	HBITMAP drawBitmap;
	RECT window_rt;
public:
	virtual void DrawScreen(HDC hdc) override;
	virtual void Init() override;
	virtual void GetMouseMove(int x, int y) override;
	virtual void Release() override;
	virtual void Update() override;

	//virtual void GetInput(WPARAM wParam) {}
	//virtual void GetKeyDown(WPARAM wParam) {}	
	//virtual void GetMouseClick(int x, int y, int E_MOUSE_BTN) {}
};