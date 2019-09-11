#pragma once
#include "GameObject.h"
#include "IMGEnum.h"
#include "Collider.h"
#include <unordered_map>
#include "FlameRingRenderer.h"
#include "Vector2D.h"

class FlameRing
	: virtual public GameObject, virtual public Colider
{
private:
	FlameRingRenderer* leftHalf;
	FlameRingRenderer* rightHalf;
	Vector2D<int> LeftHalfPos;
	Vector2D<int> RightHalfPos;
	const static int velocity = 300;
	const static int generationPoint = 12000;
	int bmwidth;
	int ringWidth;
	//void ReturnToGenerationPoint();
public:
	//void Start() {};
	void Update() override;
	~FlameRing();
	////virtual void Render(HDC hdc, int CameraX) {};
	void addRenderer(std::vector<Renderer*>& rendVec) override;
	FlameRing(std::unordered_map<IMGEnum, HBITMAP>& hBitmap, std::unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& winRect, int zLeft, int zRight, int startx, int starty);
	void MoveTo(int xpos);
	int* getXpos();
	/*std::vector<Vector2D<int>> vertexInfo;
	int Tag;
	virtual bool isCollide(Colider& dest);
	virtual void OnCollision(int destTag) {};*/
};