#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
#include "../Enemy/Goomba.h"
#include "../Enemy/Koopa.h"
#include "../Enemy/Fireball.h"

#define MUSHROOM_GRAVITY 0.001f
#define MUSHROOM_WALKING_SPEED 0.05f

#define MUSHROOM_BBOX_WIDTH 16
#define MUSHROOM_BBOX_HEIGHT 15

#define MUSHROOM_DIE_TIMEOUT 500

#define MUSHROOM_STATE_WALKING 100
#define MUSHROOM_STATE_DIE 200



class CMushroom : public CGameObject
{
protected:
	float ax;
	float ay;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
			left = x - MUSHROOM_BBOX_WIDTH / 2;
			top = y - MUSHROOM_BBOX_HEIGHT / 2;
			right = left + MUSHROOM_BBOX_WIDTH;
			bottom = top + MUSHROOM_BBOX_HEIGHT;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		vy += ay * dt;
		vx += ax * dt;

		if (state == MUSHROOM_STATE_DIE)
		{
			isDeleted = true;
			return;
		}

	
		//DebugOutTitle(L"[INFO] CMushroom::Update state: %d\n", state);
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	};


	virtual void Render()
	{
		CSprites::GetInstance()->Get(ID_SPRITE_MUSHROOM_RED)->Draw(x, y);
		//RenderBoundingBox();
	};

	virtual int IsCollidable() { return isCollidable; };
	virtual int IsBlocking() { return 0; }


	virtual void OnNoCollision(DWORD dt)
	{
		x += vx * dt;
		y += vy * dt;
	};


	virtual void OnCollisionWith(LPCOLLISIONEVENT e)
	{
		if (!e->obj->IsBlocking()) return;
		if (dynamic_cast<CMushroom*>(e->obj)) return;
		if (dynamic_cast<CGoomba*>(e->obj)) return;
		if (dynamic_cast<CFireBall*>(e->obj)) return;
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
	CMushroom(float x, float y, bool isHaveWing = 0)
	{
		this->ax = 0;
		this->ay = MUSHROOM_GRAVITY;
		SetState(MUSHROOM_STATE_WALKING);
		CGameObject::SetCollidable(true);
	}


	virtual void SetState(int state)
	{
		CGameObject::SetState(state);
		vx = -MUSHROOM_WALKING_SPEED;
		
	};
};

