#pragma once
#include "Scene.h"
#include <unordered_map>
#include <vector>
#include "IMGEnum.h"
#include "GameObject.h"
#include "CircusObjects.h"
#include "EnumCircusState.h"

class CircusScene
	: virtual public Scene
{
private:
	std::unordered_map<IMGEnum, HBITMAP> hBitmap;
	std::unordered_map<IMGEnum, BITMAP> bitmapInfo;

	std::vector<GameObject*> objectVec;
	std::vector<Renderer*> rendVec;

	std::vector<Colider*> colVec;
	HDC backBuffer;
	RECT windowRect;
	HBITMAP drawBitmap;
	
	CircusState state = CircusState::PLAYING;

	void LoadBitmaps();
	void SetBuffer();
	void SetBuffer(HDC hdc);
	void MakeObjects();
	void StartObjects();
	bool isBackBufferGenerated = false;
	int CameraX = 0;
	Player* playerInstance = nullptr;
	void CameraFollow();
	void CollisionDetect();
	// object Generater
	void GenerateMiterMark(int startx, int miter);
	void GenerateFlamePot(int startx);
	void RandomGenerateFlamePot(int start, int end, int mindist, int maxdist);
	void GenerateFlameRing(int startx);
	void RandomGenerateFlameRing(int start, int cnt, int mindist, int maxdist);
	static const int EndPos = 8080;
	static const int StartPos = 80;
	
	void RevivePlayer();
	void Regenerate(int playerX);
public:
	void Init() override;
	void Release() override;
	void DrawScreen(HDC hdc) override;
	void GetInput(WPARAM wParam) override;
	void Update() override;
	//virtual void GetMouseClick(int x, int y, int E_MOUSE_BTN) {}
	//virtual void GetMouseMove(int x, int y) {}
	//void GetKeyDown(WPARAM wParam) override; // deleted function

};

