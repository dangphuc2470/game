#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"

#define GOOMBA_GRAVITY 0.001f
#define GOOMBA_WALKING_SPEED 0.05f


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_NO_WINGS 14
#define GOOMBA_BBOX_HEIGHT_FLY_WALK 22
#define GOOMBA_BBOX_HEIGHT_FLY_FLY 23
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_DIE_TIMEOUT 500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_FLYING_WALK 300
#define GOOMBA_STATE_FLYING_FLY 400
#define GOOMBA_STATE_FLYING_NO_WINGS 500
#define GOOMBA_STATE_FLYING_DIE 600
#define GOOMBA_STATE_CHANGE_TIME_SHORT 100 //ms
#define GOOMBA_STATE_CHANGE_TIME_LONG 2000 //ms


class CGoomba : public CGameObject
{
protected:
	float ax;
	float ay;
	DWORD lastStateChange;
	int flyWalkCycle;
	DWORD flyWalkTimes[8] = { 2000, 100, 100, 100, 100, 100, 1000, 500 }; //ms
	ULONGLONG die_start;

	float GOOMBA_JUMP_SPEED = 0.1f;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		switch (state)
		{
		case GOOMBA_STATE_DIE:
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
			break;
		case GOOMBA_STATE_WALKING:
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT;
			break;
		case GOOMBA_STATE_FLYING_WALK:
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT_FLY_WALK / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT_FLY_WALK;
			break;
		case GOOMBA_STATE_FLYING_FLY:
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT_FLY_WALK / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT_FLY_WALK;
			break;
		case GOOMBA_STATE_FLYING_DIE:
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
			break;
		case GOOMBA_STATE_FLYING_NO_WINGS:
			left = x - GOOMBA_BBOX_WIDTH / 2;
			top = y - GOOMBA_BBOX_HEIGHT / 2;
			right = left + GOOMBA_BBOX_WIDTH;
			bottom = top + GOOMBA_BBOX_HEIGHT_NO_WINGS;
			break;
		default:
			DebugOutTitle(L"[ERROR] CGoomba::GetBoundingBox unknown state: %d\n", state);
		}
	
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		vy += ay * dt;
		vx += ax * dt;

		if ((state == GOOMBA_STATE_DIE || state == GOOMBA_STATE_FLYING_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
		{
			isDeleted = true;
			return;
		}

		DWORD now = GetTickCount64();
		if (state == GOOMBA_STATE_FLYING_WALK || state == GOOMBA_STATE_FLYING_FLY)
		{
			DWORD changeTime = flyWalkTimes[flyWalkCycle % 8];
			if (flyWalkCycle % 8 == 6)
				GOOMBA_JUMP_SPEED = 0.25f;
			else
				GOOMBA_JUMP_SPEED = 0.1f;
			if (now - lastStateChange >= changeTime)
			{
				if (state == GOOMBA_STATE_FLYING_WALK)
					SetState(GOOMBA_STATE_FLYING_FLY);
				else if (state == GOOMBA_STATE_FLYING_FLY)
					SetState(GOOMBA_STATE_FLYING_WALK);

				lastStateChange = now;
				flyWalkCycle = (flyWalkCycle + 1) % 8;
			}
		}

		//DebugOutTitle(L"[INFO] CGoomba::Update state: %d\n", state);
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	};


	virtual void Render()
	{
		int aniId;
		switch (state)
		{
		case GOOMBA_STATE_DIE:
			aniId = ID_ANI_GOOMBA_DIE;
			break;
		case GOOMBA_STATE_FLYING_DIE:
			aniId = ID_ANI_GOOMBA_FLY_DIE;
			break;
		case GOOMBA_STATE_FLYING_WALK:
			aniId = ID_ANI_GOOMBA_FLY_WALK;
			break;
		case GOOMBA_STATE_FLYING_FLY:
			aniId = ID_ANI_GOOMBA_FLY_FLY;
			break;
		case GOOMBA_STATE_FLYING_NO_WINGS:
			aniId = ID_ANI_GOOMBA_FLY_NO_WINGS;
			break;
		default:
			aniId = ID_ANI_GOOMBA_WALKING;
			break;
		}

		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
		RenderBoundingBox();
	};

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }


	virtual void OnNoCollision(DWORD dt)
	{
		x += vx * dt;
		y += vy * dt;
	};


	virtual void OnCollisionWith(LPCOLLISIONEVENT e)
	{
		if (!e->obj->IsBlocking()) return;
		if (dynamic_cast<CGoomba*>(e->obj)) return;

		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
		{
			vx = -vx;
		}

	};

public:
	CGoomba(float x, float y, bool isHaveWing = 0)
	{
		this->ax = 0;
		this->ay = GOOMBA_GRAVITY;
		die_start = -1;
		isHaveWing == 0 ?
		SetState(GOOMBA_STATE_WALKING):
		SetState(GOOMBA_STATE_FLYING_WALK);
		lastStateChange = GetTickCount64();
		flyWalkCycle = 0;
	}


	virtual void SetState(int state)
	{
		CGameObject::SetState(state);
		switch (state)
		{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
			vx = 0;
			vy = 0;
			ay = 0;
			break;
		case GOOMBA_STATE_FLYING_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT_FLY_WALK - GOOMBA_BBOX_HEIGHT_DIE) / 2;
			vx = 0;
			vy = 0;
			ay = 0;
			break;
		case GOOMBA_STATE_WALKING:
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_FLYING_WALK:
			if (vx == 0) 
				vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_FLYING_FLY:
			vy = -GOOMBA_JUMP_SPEED;
			break;
		case GOOMBA_STATE_FLYING_NO_WINGS:
			break;
		}
	};
};

