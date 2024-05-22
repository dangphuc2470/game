#pragma once
#include "GameObject.h"
#include "AssetIDs.h"

#define KOOPA_GRAVITY 0.002f
#define KOOPA_WALKING_SPEED 0.05f


#define KOOPA_BBOX_WIDTH 15
#define KOOPA_BBOX_HEIGHT 25
#define KOOPA_BBOX_HEIGHT_WINGS 26
#define KOOPA_BBOX_HEIGHT_DIE 7
#define KOOPA_JUMP_SPEED 0.2f

#define KOOPA_DIE_TIMEOUT 500

#define KOOPA_STATE_WALKING_GREEN 100
#define KOOPA_STATE_DIE_GREEN 200
#define KOOPA_STATE_FLY_GREEN 300
#define KOOPA_STATE_WALKING_RED 400
#define KOOPA_STATE_DIE_RED 500
#define KOOPA_STATE_FLY_RED 600


class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		if (state == KOOPA_STATE_DIE_GREEN || state == KOOPA_STATE_DIE_RED)
		{
			top = y - KOOPA_BBOX_HEIGHT_DIE / 2;
			right = left + KOOPA_BBOX_WIDTH;
			bottom = top + KOOPA_BBOX_HEIGHT_DIE;
		}
		else if (state == KOOPA_STATE_FLY_GREEN || state == KOOPA_STATE_FLY_RED)
		{
			top = y - KOOPA_BBOX_HEIGHT_WINGS / 2;
			right = left + KOOPA_BBOX_WIDTH;
			bottom = top + KOOPA_BBOX_HEIGHT_WINGS;
		}
		else
		{
			top = y - KOOPA_BBOX_HEIGHT / 2;
			right = left + KOOPA_BBOX_WIDTH;
			bottom = top + KOOPA_BBOX_HEIGHT;
		}
	};
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		vy += ay * dt;
		vx += ax * dt;

		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	};
	virtual void Render()
	{
		int aniID;
		switch (state)
		{
		case KOOPA_STATE_WALKING_GREEN:
			vx > 0 ? aniID = ID_ANI_KOOPA_WALKING_GREEN_RIGHT : aniID = ID_ANI_KOOPA_WALKING_GREEN_LEFT;
			break;
		case KOOPA_STATE_DIE_GREEN:
			aniID = ID_ANI_KOOPA_DIE_GREEN;
			break;
		case KOOPA_STATE_FLY_GREEN:
			vx > 0 ? aniID = ID_ANI_KOOPA_FLY_GREEN_RIGHT : aniID = ID_ANI_KOOPA_FLY_GREEN_LEFT;
			break;
		case KOOPA_STATE_WALKING_RED:
			vx > 0 ? aniID = ID_ANI_KOOPA_WALKING_RED_RIGHT : aniID = ID_ANI_KOOPA_WALKING_RED_LEFT;
			break;
		case KOOPA_STATE_DIE_RED:
			aniID = ID_ANI_KOOPA_DIE_RED;
			break;
		case KOOPA_STATE_FLY_RED:
			vx > 0 ? aniID = ID_ANI_KOOPA_FLY_RED_RIGHT : aniID = ID_ANI_KOOPA_FLY_RED_LEFT;
			break;
		default:
			DebugOutTitle(L"[INFO] Koopa State Error: %d\n", state);
			break;
		}
		CAnimations::GetInstance()->Get(aniID)->Render(x, y);
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
		if (dynamic_cast<CKoopa*>(e->obj)) return;

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
	CKoopa(float x, float y, bool isGreen = false, bool isHaveWings = false)
	{
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;

		if (isGreen)
		{
			if (isHaveWings)
				SetState(KOOPA_STATE_FLY_GREEN);
			else
				SetState(KOOPA_STATE_WALKING_GREEN);
		}
		else
		{
			if (isHaveWings)
				SetState(KOOPA_STATE_FLY_RED);
			else
				SetState(KOOPA_STATE_WALKING_RED);
		}

	};
	virtual void SetState(int state)
	{
		CGameObject::SetState(state);
		switch (state)
		{
		case KOOPA_STATE_WALKING_GREEN:
			vx = KOOPA_WALKING_SPEED;
			break;
		case KOOPA_STATE_DIE_GREEN:
			vx = 0;
			vy = 0;
			ay = 0;
			y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
		case KOOPA_STATE_FLY_GREEN:
			vx = KOOPA_WALKING_SPEED;
			//vy = -KOOPA_JUMP_SPEED;
			break;
		case KOOPA_STATE_WALKING_RED:
			vx = KOOPA_WALKING_SPEED;
			break;
		case KOOPA_STATE_DIE_RED:
			vx = 0;
			vy = 0;
			ay = 0;
			y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
		case KOOPA_STATE_FLY_RED:
			vx = KOOPA_WALKING_SPEED;
			//vy = -KOOPA_JUMP_SPEED;
			break;
		default:
			DebugOutTitle(L"[INFO] Koopa SetState Error: %d\n", state);
			break;
		}
	}
};