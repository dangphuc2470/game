#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
#include "../Enemy/Goomba.h"
#include "../Enemy/Koopa.h"
#include "../Enemy/Fireball.h"

#define MUSHROOM_GRAVITY 0.001f
#define MUSHROOM_WALKING_SPEED 0.05f

#define MUSHROOM_BBOX_WIDTH 12
#define MUSHROOM_BBOX_HEIGHT 15

#define MUSHROOM_DIE_TIMEOUT 500

#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_STATE_DIE 200
#define MUSHROOM_STATE_MOVING_UP 300
#define MUSHROOM_STATE_IDLE 400
#define MUSHROOM_MOVINGUP_TIME 500
#define MUSHROOM_STATE_POINT 600
class CKoopa;


class CMushroom : public CGameObject
{
protected:
	float ax;
	float ay;
	bool isRed;
	ULONGLONG movingUpTime = -1;
	ULONGLONG pointTime = -1;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
			left = x - MUSHROOM_BBOX_WIDTH / 2;
			top = y - MUSHROOM_BBOX_HEIGHT / 2;
			right = left + MUSHROOM_BBOX_WIDTH;
			bottom = top + MUSHROOM_BBOX_HEIGHT;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if (state == MUSHROOM_STATE_POINT && GetTickCount64() - pointTime > MUSHROOM_DIE_TIMEOUT)
		{
			isDeleted = true;
		}


		if (state == MUSHROOM_STATE_IDLE)
		{
			vx = 0;
			vy = 0;
			return;
		}

		if (state == MUSHROOM_STATE_MOVING_UP)
		{
			vy = -0.03f;
			if (GetTickCount64() - movingUpTime > MUSHROOM_MOVINGUP_TIME)
			{
				SetState(MUSHROOM_STATE_WALKING);
			}
		}
		else
		{
			vy += ay * dt;
			vx += ax * dt;
		}

		
	
		//DebugOutTitle(L"[INFO] CMushroom::Update state: %d\n", state);
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	};


	virtual void Render()
	{
		if (state == MUSHROOM_STATE_POINT)
		{
			if (isRed)
			CSprites::GetInstance()->Get(ID_SPRITE_POINT_1000)->Draw(x, y);
			else 
				CSprites::GetInstance()->Get(ID_SPRITE_POINT_1UP)->Draw(x, y);
			return;
		}
		if (isRed)
		CSprites::GetInstance()->Get(ID_SPRITE_MUSHROOM_RED)->Draw(x, y);
			else
		CSprites::GetInstance()->Get(ID_SPRITE_MUSHROOM_GREEN)->Draw(x, y);
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
	CMushroom(float x, float y, bool isRed = true)
	{
		this->ax = 0;
		this->ay = MUSHROOM_GRAVITY;
		this->isRed = isRed;
		SetState(MUSHROOM_STATE_IDLE);
		CGameObject::SetCollidable(true);
	}


	virtual void SetState(int state)
	{
		if (state == MUSHROOM_STATE_MOVING_UP)
		{
			vx = 0;
			movingUpTime = GetTickCount64();
		}
		else if (state == MUSHROOM_STATE_WALKING)
		{
			vx = -MUSHROOM_WALKING_SPEED;
		}
		else if (state == MUSHROOM_STATE_DIE)
		{
			vx = 0;
			vy = 0;
			isDeleted = true;
		}
		else if (state == MUSHROOM_STATE_POINT)
		{
			vx = 0;
			vy = 0;
			SetBlocking(false);
			ay = POINT_GRAVITY;
			pointTime = GetTickCount64();
		}

		CGameObject::SetState(state);
	};

	bool IsRed()
	{
		return isRed;
	}
};

