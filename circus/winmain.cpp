#include "WndBase.h"
#include "ProgramCore.h"

#pragma comment(lib, "msimg32.lib")

HINSTANCE g_hinst;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	// window handle
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hinst = hInstance;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ProgramCore::instance.setGinst(g_hinst);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int mouseXpos;
	static int mouseYpos;
	
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		mouseXpos = LOWORD(lParam);
		mouseYpos = HIWORD(lParam);
		ProgramCore::instance.GetMouseClick(mouseXpos, mouseYpos, MOUSE_LEFT_BTN);
		return 0;
	case WM_RBUTTONDOWN:
		mouseXpos = LOWORD(lParam);
		mouseYpos = HIWORD(lParam);
		ProgramCore::instance.GetMouseClick(mouseXpos, mouseYpos, MOUSE_RIGHT_BTN);
		return 0;
	case WM_MOUSEMOVE:
		mouseXpos = LOWORD(lParam);
		mouseYpos = HIWORD(lParam);
		ProgramCore::instance.GetMouseMove(mouseXpos, mouseYpos);
		return 0;
	case WM_KEYDOWN:
		ProgramCore::instance.GetKeyDown(wParam);
		return 0;
	case WM_KEYUP:
		ProgramCore::instance.GetKeyUp(wParam);
		return 0;
	case WM_CHAR:
		ProgramCore::instance.GetInput(wParam);
		return 0;
	case WM_TIMER:
		ProgramCore::instance.Update();
		return 0;
	case WM_CREATE:
		ProgramCore::instance.SetHWND(hWnd);
		ProgramCore::instance.Init();
		return 0;
	case WM_DESTROY:
		ProgramCore::instance.Release();
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		ProgramCore::instance.DrawScreen(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}