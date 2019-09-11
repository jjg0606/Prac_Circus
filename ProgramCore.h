#pragma once
#include "Scene.h"
#include <time.h>

class ProgramCore
{
private:
	ProgramCore();
	Scene* curScene;
	Scene* nextScene;
	unsigned int hTimer;
	HWND hWnd;
	HDC memDC;
	HINSTANCE g_inst;
	void(ProgramCore::*UpdateLast)();
	void DoNothing();
	void ChangeSceneU();
	int cntInputKey;
	bool* inputArr;

	clock_t beforeTime;
	float deltaTime;
public:
	static ProgramCore instance;
	void setGinst(HINSTANCE _g_inst);
	HINSTANCE getGinst();
	void ChangeScene(Scene* scene);
	void SetMemDC(HDC _memDC);
	HDC getMemDC();
	void Release();
	void Init();
	void DrawScreen(HDC hdc);
	void GetInput(WPARAM wParam);
	void GetKeyDown(WPARAM wParam);
	void GetKeyUp(WPARAM wParam);
	bool GetKey(WPARAM keyName);
	void Update();
	void GetMouseClick(int x, int y, int E_MOUSE_BTN);
	void GetMouseMove(int x, int y);
	void SetUpdateIntersec(int mtime);
	void DeleteTimer();
	void SetHWND(HWND hWnd);
	HWND getHWND();
	float getDeltaTime();
	void Invalidate();
};
