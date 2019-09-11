#include "CircusScene.h"
#include "ProgramCore.h"
#include <algorithm>

using namespace std;

void CircusScene::Init()
{
	SetBuffer();
	LoadBitmaps();
	MakeObjects();
	StartObjects();
	ProgramCore::instance.SetUpdateIntersec(0);
}

void CircusScene::MakeObjects()
{
	int floorHeight = bitmapInfo[IMGEnum::BACK].bmHeight;
	int miterMarkHeight = bitmapInfo[IMGEnum::MITER].bmHeight;
	Floor* floor = new Floor(hBitmap, bitmapInfo, windowRect,0, 0, windowRect.bottom - bitmapInfo[IMGEnum::BACK].bmHeight);
	objectVec.push_back(floor);

	BackDecoPattern* deco = new BackDecoPattern(hBitmap, bitmapInfo, windowRect, 0, 0, windowRect.bottom - bitmapInfo[IMGEnum::BACK].bmHeight - bitmapInfo[IMGEnum::BACK_DECO].bmHeight);	
	objectVec.push_back(deco);
	deco->SetSceneStatePointer(&state);

	Player* player = new Player(hBitmap, bitmapInfo, windowRect, 2, StartPos, windowRect.bottom - miterMarkHeight - bitmapInfo[IMGEnum::PLAYER0].bmHeight);
	objectVec.push_back(player);
	playerInstance = player;
	playerInstance->SetSceneStatePointer(&state);

	int distance = (EndPos - StartPos)/10;
	for (int i = 0; i <= 10; i++)
	{
		GenerateMiterMark(StartPos + distance * i, 100 - 10 * i);
	}
	
	UIRenderer* uiRenderer = new UIRenderer(hBitmap, bitmapInfo, windowRect, 0, playerInstance);
	objectVec.push_back(uiRenderer);

	// end Guard
	int PotEndPoint = EndPos - bitmapInfo[IMGEnum::FRONT].bmWidth;
	maxPotPos = PotEndPoint - 2 * bitmapInfo[IMGEnum::FRONT].bmWidth;
	GenerateFlamePot(PotEndPoint);
	potvec.clear();
	int PotStartPoint = StartPos + 10 * bitmapInfo[IMGEnum::FRONT].bmWidth;
	RandomGenerateFlamePot(PotStartPoint , maxPotPos, minPotDist, maxPotDist);
	RandomGenerateFlameRing(StartPos + windowRect.right, gringCnt, minRingDist, maxRingDist);

	EndTrampoline* endTramp = new EndTrampoline(hBitmap, bitmapInfo, windowRect, 3, EndPos, windowRect.bottom - miterMarkHeight - bitmapInfo[IMGEnum::END].bmHeight);
	objectVec.push_back(endTramp);
	colVec.push_back(endTramp);
}

void CircusScene::StartObjects()
{
	for (int i = 0; i < objectVec.size(); i++)
	{
		objectVec[i]->Start();
		objectVec[i]->addRenderer(rendVec);
	}
	sort(rendVec.begin(), rendVec.end(), [](Renderer* rend1, Renderer* rend2) ->bool{
		return rend1->zIndex < rend2->zIndex;
	});
}

void CircusScene::Release()
{
	SelectObject(ProgramCore::instance.getMemDC(), oldMap);
	for (int i = 0; i < objectVec.size(); i++)
	{
		delete objectVec[i];
	}

	for (auto iter = hBitmap.begin(); iter != hBitmap.end(); iter++)
	{
		DeleteObject((*iter).second);
	}
	ReleaseDC(ProgramCore::instance.getHWND(), backBuffer);
	ReleaseDC(ProgramCore::instance.getHWND(), ProgramCore::instance.getMemDC());
}

void CircusScene::LoadBitmaps()
{
	hBitmap[IMGEnum::BACK] = (HBITMAP)LoadImage(NULL, L"res/back.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::BACK_DECO] = (HBITMAP)LoadImage(NULL, L"res/back_deco.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::BACK_NORMAL] = (HBITMAP)LoadImage(NULL, L"res/back_normal.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::BACK_NORMAL2] = (HBITMAP)LoadImage(NULL, L"res/back_normal2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::CASH] = (HBITMAP)LoadImage(NULL, L"res/cash.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::DIE] = (HBITMAP)LoadImage(NULL, L"res/die.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::END] = (HBITMAP)LoadImage(NULL, L"res/end.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::ENEMY] = (HBITMAP)LoadImage(NULL, L"res/enemy.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::ENEMY1] = (HBITMAP)LoadImage(NULL, L"res/enemy_1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::ENEMY_1B] = (HBITMAP)LoadImage(NULL, L"res/enemy_1b.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::ENEMY_1F] = (HBITMAP)LoadImage(NULL, L"res/enemy_1f.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::ENEMY_B] = (HBITMAP)LoadImage(NULL, L"res/enemy_b.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::ENEMY_F] = (HBITMAP)LoadImage(NULL, L"res/enemy_f.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::ENEMY_L] = (HBITMAP)LoadImage(NULL, L"res/enemy_l.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::ENEMY_L_B] = (HBITMAP)LoadImage(NULL, L"res/enemy_l_b.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::ENEMY_L_F] = (HBITMAP)LoadImage(NULL, L"res/enemy_l_f.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::FRONT] = (HBITMAP)LoadImage(NULL, L"res/front.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::FRONT2] = (HBITMAP)LoadImage(NULL, L"res/front2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::ICON] = (HBITMAP)LoadImage(NULL, L"res/icon.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::MITER] = (HBITMAP)LoadImage(NULL, L"res/miter.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::PLAYER0] = (HBITMAP)LoadImage(NULL, L"res/player0.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::PLAYER1] = (HBITMAP)LoadImage(NULL, L"res/player1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::PLAYER2] = (HBITMAP)LoadImage(NULL, L"res/player2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::STAR] = (HBITMAP)LoadImage(NULL, L"res/star.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::STAR1] = (HBITMAP)LoadImage(NULL, L"res/star1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::STAR2] = (HBITMAP)LoadImage(NULL, L"res/star2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::WIN] = (HBITMAP)LoadImage(NULL, L"res/win.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBitmap[IMGEnum::WIN2] = (HBITMAP)LoadImage(NULL, L"res/win2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	for (auto iter = hBitmap.begin(); iter != hBitmap.end(); iter++)
	{
		bitmapInfo[(*iter).first] = BITMAP{};
		GetObject(hBitmap[(*iter).first] , sizeof(BITMAP), &bitmapInfo[(*iter).first]);				
	}

	oldMap = (HBITMAP)SelectObject(ProgramCore::instance.getMemDC(), hBitmap.begin()->second);
	SelectObject(ProgramCore::instance.getMemDC(), oldMap);
}

void CircusScene::DrawScreen(HDC hdc)
{
	FillRect(backBuffer, &windowRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
	for (int i = 0; i < rendVec.size(); i++)
	{
		rendVec[i]->Render(backBuffer, CameraX);
	}
	
	// for debug
	/*static wchar_t buf[256];
	int pxmin, pxmax, rxmin, rxmax , dummy;
	playerInstance->getMinMax(pxmin, pxmax, dummy, dummy);
	colVec[0]->getMinMax(rxmin, rxmax, dummy, dummy);
	wsprintf(buf, TEXT("Player location %d, %d , Ring location %d, %d, AngleSum %d"), pxmin, pxmax, rxmin, rxmax,(int)getMaxAngleSum());
	TextOut(hdc, 0, 0, buf,lstrlen(buf));*/
#ifdef DEBUG_MODE
	playerInstance->DrawColider(backBuffer, CameraX);
	for (int i = 0; i < colVec.size(); i++)
	{
		colVec[i]->DrawColider(backBuffer, CameraX);
	}
#endif
	// debug end
	BitBlt(hdc, 0, 0, windowRect.right, windowRect.bottom, backBuffer, 0, 0, SRCCOPY);
}

void CircusScene::Update()
{
	if (state == CircusState::PLAYER_REVIVE)
	{
		RevivePlayer();
	}
	if (state != CircusState::PLAYING)
	{
		ProgramCore::instance.Invalidate();
		return;
	}
	for (int i = 0; i < objectVec.size(); i++)
	{
		objectVec[i]->Update();
	}

	CollisionDetect();
	CameraFollow();

	ProgramCore::instance.Invalidate();
}

void CircusScene::SetBuffer()
{
	GetClientRect(ProgramCore::instance.getHWND(), &windowRect);

	HDC temDC = GetDC(ProgramCore::instance.getHWND());

	backBuffer = CreateCompatibleDC(temDC);
	drawBitmap = CreateCompatibleBitmap(temDC, windowRect.right, windowRect.bottom);
	SelectObject(backBuffer, drawBitmap);
	ProgramCore::instance.SetMemDC(CreateCompatibleDC(backBuffer));
	
	ReleaseDC(ProgramCore::instance.getHWND(), temDC);
}

void CircusScene::SetBuffer(HDC hdc)
{
	backBuffer = CreateCompatibleDC(hdc);
	drawBitmap = CreateCompatibleBitmap(backBuffer, windowRect.right, windowRect.bottom);
	SelectObject(backBuffer, drawBitmap);
	ProgramCore::instance.SetMemDC(CreateCompatibleDC(backBuffer));
}

void CircusScene::GetInput(WPARAM wParam)
{
}

void CircusScene::CameraFollow()
{
	static int PlayerLeftMax = 10;
	static int PlayerRightMax = 180;

	// 플레이어의 화면상의 좌표
	int curPlayerx = playerInstance->Vpos.x - CameraX;
	
	int dist = 0;
	if (curPlayerx < PlayerLeftMax)
	{
		dist = curPlayerx - PlayerLeftMax;
	}
	else if (curPlayerx > PlayerRightMax)
	{
		dist = curPlayerx - PlayerRightMax;
	}
	CameraX += dist;

	int maxCameraX = EndPos - windowRect.right + 100;
	if (CameraX < minCameraX)
	{
		CameraX = minCameraX;
	}
	else if (CameraX > maxCameraX)
	{
		CameraX = maxCameraX;
	}
}

void CircusScene::CollisionDetect()
{
	for (int i = 0; i < colVec.size(); i++)
	{
		if (playerInstance->isCollide(*colVec[i]))
		{
			playerInstance->OnCollision(colVec[i]->Tag);
			colVec[i]->OnCollision(playerInstance->Tag);
		}
	}
}

void CircusScene::GenerateMiterMark(int startx, int miter)
{
	MiterMark* nmark = new MiterMark(hBitmap, bitmapInfo, windowRect, 3, startx, windowRect.bottom - bitmapInfo[IMGEnum::MITER].bmHeight, miter);
	objectVec.push_back(nmark);
}

void CircusScene::GenerateFlamePot(int startx)
{
	int potWidth = bitmapInfo[IMGEnum::FRONT].bmWidth;
	int potHeight = bitmapInfo[IMGEnum::FRONT].bmHeight;
	FlamePot* fpot = new FlamePot(hBitmap, bitmapInfo, windowRect, 1, startx, windowRect.bottom - bitmapInfo[IMGEnum::MITER].bmHeight - bitmapInfo[IMGEnum::FRONT].bmHeight);
	objectVec.push_back(fpot);
	colVec.push_back(fpot);
	potvec.push_back(fpot);
	
	MiddleObstacle* mo = new MiddleObstacle(fpot->getXpos(), startx, windowRect.bottom - bitmapInfo[IMGEnum::MITER].bmHeight - 2 * potHeight, startx + potWidth, windowRect.bottom - bitmapInfo[IMGEnum::MITER].bmHeight - bitmapInfo[IMGEnum::FRONT].bmHeight);
	objectVec.push_back(mo);
	colVec.push_back(mo);
}

void CircusScene::GenerateFlameRing(int startx)
{
	FlameRing* fring = new FlameRing(hBitmap, bitmapInfo, windowRect, 1, 3, startx, windowRect.bottom - bitmapInfo[IMGEnum::BACK].bmHeight);
	objectVec.push_back(fring);
	colVec.push_back(fring);
	ringvec.push_back(fring);
	MiddleObstacle* mo = new MiddleObstacle(fring->getXpos(), startx, windowRect.bottom - bitmapInfo[IMGEnum::BACK].bmHeight
		, startx + bitmapInfo[IMGEnum::ENEMY_F].bmWidth, windowRect.bottom - bitmapInfo[IMGEnum::BACK].bmHeight + bitmapInfo[IMGEnum::ENEMY_F].bmHeight);
	objectVec.push_back(mo);
	colVec.push_back(mo);
}

void CircusScene::RandomGenerateFlamePot(int start, int end, int mindist, int maxdist)
{
	static auto getDist = [mindist, maxdist]() ->int{
		return rand() % (maxdist - mindist);
	};

	int next = start + getDist();;
	while (next < end)
	{
		GenerateFlamePot(next);
		next += getDist() + mindist;
	}
}

void CircusScene::RandomGenerateFlameRing(int start, int cnt, int mindist, int maxdist)
{
	static auto getDist = [mindist, maxdist]() ->int {
		return rand() % (maxdist - mindist);
	};

	int next = start + getDist();
	int cntRing = 0;
	while (cntRing < cnt)
	{
		GenerateFlameRing(next);
		next += getDist() + mindist;
		cntRing++;
	}
}

void CircusScene::RevivePlayer()
{
	playerInstance->Vpos.y = windowRect.bottom - bitmapInfo[IMGEnum::MITER].bmHeight - bitmapInfo[IMGEnum::PLAYER0].bmHeight;
	if (playerInstance->Vpos.x < StartPos)
	{
		playerInstance->Vpos.x = StartPos;		
	}
	else
	{
		int curX = playerInstance->Vpos.x;
		curX -= StartPos;
		int dX = (EndPos - StartPos) / 10;
		int miteridx = curX / dX;
		playerInstance->Vpos.x = StartPos + miteridx * dX;

	}

	playerInstance->SetColider();
	Regenerate(playerInstance->Vpos.x);
	state = CircusState::PLAYING;
}

void CircusScene::Regenerate(int playerX)
{
	int nextX = playerX +100+ rand()%(maxPotDist-minPotDist);
	for (int i = 0; i < potvec.size(); i++)
	{
		if (nextX > maxPotPos)
		{
			potvec[i]->Moveto(-20); // 저세상으로 보냄
			continue;
		}

		potvec[i]->Moveto(nextX);
		nextX += minPotDist + rand() % (maxPotDist - minPotDist);
	}

	nextX = playerX + windowRect.right + rand()%(maxRingDist-minRingDist);
	for (int i = 0; i < ringvec.size(); i++)
	{
		ringvec[i]->MoveTo(nextX);
		nextX += minRingDist + rand() % (maxRingDist - minRingDist);
	}
}