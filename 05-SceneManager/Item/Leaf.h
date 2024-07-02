#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
#include "Mushroom.h"
#include "../Enemy/Goomba.h"
#include "../Enemy/Koopa.h"
#include "../Enemy/Fireball.h"

#define LEAF_UP_SPEED 0.001f
#define LEAF_GRAVITY 0.0009f
#define LEAF_FALLING_SPEED 0.05f

#define LEAF_BBOX_WIDTH 15
#define LEAF_BBOX_HEIGHT 15

#define LEAF_DIE_TIMEOUT 500

#define LEAF_STATE_FALLING 100
#define LEAF_STATE_DIE 200
#define LEAF_STATE_MOVING_UP 300
#define LEAF_STATE_IDLE 400
#define LEAF_MOVINGUP_TIME 500
#define LEAF_STATE_POINT 600

#define LEAF_STATE_CHANGE_TIME 800
class CKoopa;
class CMushroom;


class CLeaf : public CGameObject
{
protected:
	float ax;
	float ay;
	bool isGoingLeft = true;
	ULONGLONG changeDirectionTime = -1;
	ULONGLONG movingUpTime = -1;
	ULONGLONG pointTime = -1;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
			left = x - LEAF_BBOX_WIDTH / 2;
			top = y - LEAF_BBOX_HEIGHT / 2;
			right = left + LEAF_BBOX_WIDTH;
			bottom = top + LEAF_BBOX_HEIGHT;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if (state == LEAF_STATE_POINT && GetTickCount64() - pointTime > LEAF_DIE_TIMEOUT)
		{
			isDeleted = true;
		}

		if (state == LEAF_STATE_FALLING && GetTickCount64() - changeDirectionTime > LEAF_STATE_CHANGE_TIME)
		{
			isGoingLeft = !isGoingLeft;
			vx = -vx;
			changeDirectionTime = GetTickCount64();
		}

		if (state == LEAF_STATE_IDLE)
		{
			vx = 0;
			vy = 0;
			return;
		}

		if (state == LEAF_STATE_MOVING_UP)
		{
			vy = -0.03f;
			if (GetTickCount64() - movingUpTime > LEAF_MOVINGUP_TIME)
			{
				SetState(LEAF_STATE_FALLING);
			}
		}
		else
		{
			vy = ay * dt;
			vx += ax * dt;

		}

		
	
		//DebugOutTitle(L"[INFO] CLeaf::Update state: %d\n", state);
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	};


	virtual void Render()
	{
		if (state == LEAF_STATE_POINT)
		{
			CSprites::GetInstance()->Get(ID_SPRITE_POINT_1000)->Draw(x, y);
			
			return;
		}
		
		if (isGoingLeft)
		CSprites::GetInstance()->Get(ID_SPRITE_LEAF_LEFT)->Draw(x, y);
				else
			CSprites::GetInstance()->Get(ID_SPRITE_LEAF_RIGHT)->Draw(x, y);
		//RenderBoundingBox();
	};

	virtual int IsCollidable() { return isCollidable; };
	virtual int IsBlocking() { return 0; }


	virtual void OnNoCollision(DWORD dt)
	{
		x += vx * dt;
		y += vy * dt;
	};


	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CLeaf(float x, float y, bool isRed = true)
	{
		this->ax = 0;
		this->ay = LEAF_UP_SPEED;
		SetState(LEAF_STATE_IDLE);
		CGameObject::SetCollidable(false);
	}


	virtual void SetState(int state)
	{
		if (state == LEAF_STATE_MOVING_UP)
		{
			vx = 0;
			movingUpTime = GetTickCount64();
			SetBlocking(false);
		}
		else if (state == LEAF_STATE_FALLING)
		{
			ay = LEAF_GRAVITY;
			vx = -LEAF_FALLING_SPEED;
			changeDirectionTime = GetTickCount64();
		}
		else if (state == LEAF_STATE_DIE)
		{
			vx = 0;
			vy = 0;
			isDeleted = true;
		}
		else if (state == LEAF_STATE_POINT)
		{
			vx = 0;
			vy = 0;
			SetBlocking(false);
			ay = POINT_GRAVITY;
			pointTime = GetTickCount64();
		}

		CGameObject::SetState(state);
	};

	virtual void ChangeToMushroom();
};

