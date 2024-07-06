#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
#include "../Scene/PlayScene.h"

#define FIREBALL_NEW_WIDTH 7
#define FIREBALL_NEW_HEIGHT 10
#define FIREBALL_NEW_DISTANCE_LAST 10

class CFireballnew : public CGameObject
{
protected:
	float ax = 0;
	float ay = 0;
	float start_x;
	float start_y;


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) override {
		left = x - FIREBALL_NEW_WIDTH / 2;
		top = y - FIREBALL_NEW_HEIGHT / 2;
		right = left + FIREBALL_NEW_WIDTH;
		bottom = top + FIREBALL_NEW_HEIGHT;
	}
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		vy += ay * dt;
		vx += ax * dt;

		float dx = abs(start_x - x);
		float dy = abs(start_y - y);
		if (dx > FIREBALL_NEW_DISTANCE_LAST || dy > FIREBALL_NEW_DISTANCE_LAST) {
			isDeleted = true;
		}

		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	virtual void Render()
	{
		//CAnimations::GetInstance()->Get(ID_ANI_FIREBALL)->Render(x, y);

		//RenderBoundingBox();
	}

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt)
	{
		x += vx * dt;
		if (abs(start_x - x) > FIREBALL_NEW_DISTANCE_LAST)
			{
			isDeleted = true;
		}
		y += vy * dt;
	}

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFireballnew(float x, float y, float velocityX, float velocityY) :CGameObject(x, y)
	{
		this->ax = velocityX;
		this->ay = velocityY;
		start_x = x;
		start_y = y;
	}
};







