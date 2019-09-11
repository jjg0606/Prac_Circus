#pragma once

#include "GameObject.h"
#include "IMGEnum.h"
#include <unordered_map>
#include "PlayerAnimRender.h"
#include "Collider.h"
#include "Vector2D.h"
#include "EnumCircusState.h"

enum class PLAYER_STATE
{
	IDLE,
	MOVE_FORWARD,
	MOVE_BACKWARD,
	JUMP,
	FORWARD_JUMP,
};

class Player
	: virtual public GameObject, virtual public Renderer, virtual public Colider
{
	//int zIndex; from renderer
	RECT& winRect;
	PLAYER_STATE state;
	PlayerAnimRender* animRenderer;

	int playerWidth = 0;
	int playerHeight = 0;

	int jumpTimeCnt = 0;
	static const int JumpMultiple = 2;

	int groundY;
	void ProceedJump();
	bool moveBeforeJump = false;
	CircusState* SceneState = nullptr;
	const static int Speed = 200;
	const static int JumpingHeight = 70;
	void SetState();
	void UpdateColider(int dx,int dy);
	int score = 0;
	int cntMiddleObs = 0;

	int Life = 10;
	int cntDieAnim = 0;
	static const int DieAnimPlayTime = 100;
	void Revive();

public:
	Vector2D<int> Vpos{ 0,0 };
	void Start() override;
	void Update() override;
	~Player();
	int getScore();
	void addRenderer(std::vector<Renderer*>& rendVec) override;
	void Render(HDC hdc, int CameraX) override;
	Player(std::unordered_map<IMGEnum, HBITMAP>& hBitmap, std::unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& winRect, int zIndex, int startx, int starty);
	void GetInput(WPARAM wParam);
	void SetColider();
	void OnCollision(int destTag) override;
	void SetSceneStatePointer(CircusState* _state);
	void addScore(int score);
	int getLife();
	/*int Tag;
	virtual bool isCollide(Colider& dest);
	*/
	//std::vector<Vector2D<int>> vertexInfo;
};