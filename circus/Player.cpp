#include "Player.h"
#include "ProgramCore.h"
#include <math.h>

using namespace std;

Player::Player(unordered_map<IMGEnum, HBITMAP>& hBitmap, unordered_map<IMGEnum, BITMAP>& bitmapInfo, RECT& _winRect, int _zIndex, int _startx, int _starty)
	: winRect(_winRect)
{
	Vpos.x = _startx;
	Vpos.y = _starty;
	Renderer::zIndex = _zIndex;
	state = PLAYER_STATE::IDLE;	
	groundY = _starty;
	score = 0;
	animRenderer = new PlayerAnimRender(hBitmap, bitmapInfo);

	Colider::Tag = COL_TAG_PLAYER;
	playerWidth = bitmapInfo[IMGEnum::PLAYER0].bmWidth;
	playerHeight = bitmapInfo[IMGEnum::PLAYER0].bmHeight;

	vertexInfo.push_back({ _startx,_starty });
	vertexInfo.push_back({ _startx + playerWidth, _starty });
	vertexInfo.push_back({ _startx + playerWidth,_starty + playerHeight });
	vertexInfo.push_back({ _startx , _starty + playerHeight });
}

void Player::Start()
{
}

void Player::Update()
{
	SetState();

	if (state == PLAYER_STATE::JUMP || state == PLAYER_STATE::FORWARD_JUMP)
	{
		ProceedJump();
	}
	else if (state == PLAYER_STATE::MOVE_FORWARD)
	{
		int dx = Speed * getDeltaTime();
		this->Vpos.x += dx;
		UpdateColider(dx, 0);
	}
	else if (state == PLAYER_STATE::MOVE_BACKWARD)
	{
		int dx = -Speed * getDeltaTime();
		this->Vpos.x += dx;
		UpdateColider(dx, 0);
	}
}

void Player::SetState()
{
	if (GetKey(VK_RIGHT))
	{
		if (state == PLAYER_STATE::IDLE || state == PLAYER_STATE::MOVE_BACKWARD)
		{
			state = PLAYER_STATE::MOVE_FORWARD;
		}
	}
	if (GetKey(VK_LEFT))
	{
		if (state == PLAYER_STATE::IDLE || state == PLAYER_STATE::MOVE_FORWARD)
		{
			state = PLAYER_STATE::MOVE_BACKWARD;
		}
	}
	if (GetKey(VK_SPACE))
	{
		if (state == PLAYER_STATE::MOVE_FORWARD)
		{
			state = PLAYER_STATE::FORWARD_JUMP;
		}
		else if (state == PLAYER_STATE::IDLE || state == PLAYER_STATE::MOVE_BACKWARD)
		{
			state = PLAYER_STATE::JUMP;
		}
	}
	if (GetKey(NULL))
	{
		if (state == PLAYER_STATE::MOVE_FORWARD || state == PLAYER_STATE::MOVE_BACKWARD)
		{
			state = PLAYER_STATE::IDLE;
		}
	}
}

void Player::Render(HDC hdc, int CameraX)
{
	if (*SceneState == CircusState::PLAYING)
	{
		switch (state)
		{
		case PLAYER_STATE::IDLE:
			animRenderer->RenderIdle(hdc, CameraX, Vpos.x, Vpos.y);
			break;
		case PLAYER_STATE::JUMP:
		case PLAYER_STATE::FORWARD_JUMP:
			animRenderer->RenderJump(hdc, CameraX, Vpos.x, Vpos.y);
			break;
		case PLAYER_STATE::MOVE_FORWARD:
		case PLAYER_STATE::MOVE_BACKWARD:
			animRenderer->RenderMove(hdc, CameraX, Vpos.x, Vpos.y);
			break;
		}
	}
	else if (*SceneState == CircusState::PLAYER_DIE || *SceneState == CircusState::PLAYER_REVIVE)
	{
		cntDieAnim++;
		if (cntDieAnim > DieAnimPlayTime)
		{
			cntDieAnim = 0;
			*SceneState = CircusState::PLAYER_REVIVE;
		}
		else
		{
			animRenderer->RenderDie(hdc, CameraX, Vpos.x, Vpos.y);
		}
	}
	else if (*SceneState == CircusState::PLAYER_WIN)
	{
		animRenderer->RenderWin(hdc, CameraX, Vpos.x, Vpos.y);
	}
	
}

void Player::Revive()
{

}

Player::~Player()
{

}

void Player::GetInput(WPARAM wParam)
{
}

void Player::ProceedJump()
{
	if (jumpTimeCnt * JumpMultiple > 180)
	{
		jumpTimeCnt = 0;
		state = PLAYER_STATE::IDLE;
		return;
	}

	jumpTimeCnt++;
	int dx = state == PLAYER_STATE::FORWARD_JUMP ? Speed * ProgramCore::instance.getDeltaTime() : 0;
	Vpos.x += dx;

	static auto toRad = [](int degree) {
		return degree * 3.141592f / 180.0f;
	};

	int nextY = groundY - JumpingHeight * sin(toRad(JumpMultiple * jumpTimeCnt));
	int dy = nextY - Vpos.y;
	Vpos.y = nextY;

	UpdateColider(dx, dy);

}

void Player::addRenderer(vector<Renderer*>& rendVec)
{
	rendVec.push_back(this);
}

void Player::UpdateColider(int dx,int dy)
{
	for (int i = 0; i < vertexInfo.size(); i++)
	{
		vertexInfo[i].x += dx;
		vertexInfo[i].y += dy;
	}
}


void Player::OnCollision(int destTag)
{
	switch (destTag)
	{
	case COL_TAG_OBSTACLE:
		*SceneState = CircusState::PLAYER_DIE;
		state = PLAYER_STATE::IDLE;
		jumpTimeCnt = 0;
		break;
	case COL_TAG_MONEY:
		score += 100;
		break;
	case COL_TAG_END:
		*SceneState = CircusState::PLAYER_WIN;
		break;
	default:
		break;
	}
}

int Player::getScore()
{
	return score;
}

void Player::SetSceneStatePointer(CircusState* _state)
{
	this->SceneState = _state;
}

void Player::SetColider()
{
	int curX = Vpos.x;
	int curY = Vpos.y;
	
	vertexInfo[0] = { curX,curY };
	vertexInfo[1] = { curX + playerWidth, curY };
	vertexInfo[2] = { curX + playerWidth,curY + playerHeight };
	vertexInfo[3] = { curX , curY + playerHeight };
}