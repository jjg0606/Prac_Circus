#include "ProgramCore.h"

ProgramCore ProgramCore::instance;

ProgramCore::ProgramCore()
{
	curScene = nullptr;
	hTimer = 0;
	cntInputKey = 0;
	UpdateLast = &ProgramCore::DoNothing;
	beforeTime = time(NULL);
	int arrSize = 1 + 1 << 15;
	inputArr = new bool[arrSize];
	for (int i = 0; i < arrSize; i++)
	{
		inputArr[i] = false;
	}
	
}

void ProgramCore::Release()
{
	if (curScene != nullptr)
	{
		curScene->Release();
		delete curScene;
	}
	if (this->hTimer != 0)
	{
		KillTimer(hWnd, hTimer);
	}
	delete[] inputArr;
	DeleteDC(memDC);
}

void ProgramCore::ChangeScene(Scene* scene)
{
	this->nextScene = scene;
	this->UpdateLast = &ProgramCore::ChangeSceneU;
	SetUpdateIntersec(1);
}



void ProgramCore::DrawScreen(HDC hdc)
{
	if (curScene == nullptr)
	{
		return;
	}

	curScene->DrawScreen(hdc);
}

void ProgramCore::GetInput(WPARAM wParam)
{
	if (curScene == nullptr)
	{
		return;
	}
	curScene->GetInput(wParam);
}

bool ProgramCore::GetKey(WPARAM keyName)
{
	if (keyName == NULL)
	{
		return cntInputKey == 0;
	}
	return inputArr[keyName];
}

void ProgramCore::GetKeyDown(WPARAM wParam)
{
	//inputChar = LOWORD(wParam);
	if (!inputArr[LOWORD(wParam)])
	{
		inputArr[LOWORD(wParam)] = true;
		cntInputKey++;
	}
	
}

void ProgramCore::GetKeyUp(WPARAM wParam)
{
	if (inputArr[LOWORD(wParam)])
	{
		inputArr[LOWORD(wParam)] = false;
		cntInputKey--;
	}
}

void ProgramCore::Update()
{
	clock_t curtime = clock();
	deltaTime = (curtime - beforeTime) * 0.001f;

	beforeTime = curtime;

	if (curScene != nullptr)
	{
		curScene->Update();
	}

	(this->*UpdateLast)();
}

void ProgramCore::GetMouseClick(int x, int y, int E_MOUSE_BTN)
{
	if (curScene == nullptr)
	{
		return;
	}
	curScene->GetMouseClick(x, y, E_MOUSE_BTN);
}

void ProgramCore::GetMouseMove(int x, int y)
{
	if (curScene == nullptr)
	{
		return;
	}
	curScene->GetMouseMove(x, y);
}

void ProgramCore::SetUpdateIntersec(int mtime)
{
	if (this->hTimer != 0)
	{
		KillTimer(hWnd, hTimer);
	}
	SetTimer(hWnd, ++hTimer, mtime, NULL);
}

void ProgramCore::DeleteTimer()
{
	if (this->hTimer != 0)
	{
		KillTimer(hWnd, hTimer);
	}
	this->hTimer = 0;
}

void ProgramCore::DoNothing()
{
	// Nothing
}

void ProgramCore::ChangeSceneU()
{
	// change
	if (curScene != nullptr)
	{
		curScene->Release();
		delete curScene;
	}
	DeleteTimer();
	curScene = nextScene;
	nextScene = nullptr;
	UpdateLast = &ProgramCore::DoNothing;

	curScene->Init();
}

void ProgramCore::SetHWND(HWND hWnd)
{
	this->hWnd = hWnd;
}

float ProgramCore::getDeltaTime()
{
	return this->deltaTime;
}

void ProgramCore::SetMemDC(HDC _memDC)
{
	this->memDC = _memDC;
}


void ProgramCore::setGinst(HINSTANCE _g_inst)
{
	this->g_inst = _g_inst;
}

HINSTANCE ProgramCore::getGinst()
{
	return this->g_inst;
}

HDC ProgramCore::getMemDC()
{
	return memDC;
}

HWND ProgramCore::getHWND()
{
	return hWnd;
}

void ProgramCore::Invalidate()
{
	InvalidateRect(hWnd, NULL, FALSE);
}