#pragma once
#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
#include "../Mario.h"
#define PTOOIE_SPEED 0.05f

#define PTOOIE_BBOX_WIDTH 15
#define PTOOIE_BBOX_HEIGHT 23

#define PTOOIE_STATE_EXTEND 100
#define PTOOIE_STATE_RETRACT 200
#define PTOOIE_STATE_DIE 300
#define PIPE_WIDTH 20


class CPtooie : public CGameObject
{
protected:
	bool isMovingUp = false;
	float targetY;
	float retractY; 
	DWORD timeToStayUp = 3000; 
	DWORD timeToStayDown = 3000; 
	DWORD lastMoveTime; 
	CGameObject* mario;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x - PTOOIE_BBOX_WIDTH / 2;
		top = y - PTOOIE_BBOX_HEIGHT / 2;
		right = left + PTOOIE_BBOX_WIDTH;
		bottom = top + PTOOIE_BBOX_HEIGHT;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		DWORD now = GetTickCount64();
		float marioX, marioY;
		CMario* marioObj = dynamic_cast<CMario*>(mario);
		marioObj->GetPosition(marioX, marioY);
		float distance = abs(marioX - this->x);

		if (distance < PIPE_WIDTH)
		{
			DebugOutTitle(L"Be hon");
			if (now - lastMoveTime > timeToStayUp)
			{
				vy = -PTOOIE_SPEED;
				SetState(PTOOIE_STATE_RETRACT);
			}
			if (y < targetY)
			y = targetY;
			else if (y > retractY)
				y = retractY;
		}
		else
		if (state == PTOOIE_STATE_EXTEND)
		{
			DebugOutTitle(L"Lon hon");
			if (y > targetY)
			{
				vy = -PTOOIE_SPEED;
			}
			else
			{
				vy = 0;
				if (y < targetY)
				{
					y = targetY;
				}
				if (now - lastMoveTime > timeToStayUp)
					SetState(PTOOIE_STATE_RETRACT);
			}
		}
		else if (state == PTOOIE_STATE_RETRACT)
		{
			DebugOutTitle(L"Lon hon");

			if (y < retractY)
			{
				vy = PTOOIE_SPEED;
			}
			else
			{
				vy = 0;
				if (y > retractY)
				{
					y = retractY;
				}
				if (now - lastMoveTime > timeToStayUp)
					SetState(PTOOIE_STATE_EXTEND);
			}
		}
		else if (state == PTOOIE_STATE_DIE)
		{
			vy = 0;
			isDeleted = true;
		}


		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	};


	virtual void Render()
	{
		int aniId;
		float marioX, marioY;
		CMario* marioObj = dynamic_cast<CMario*>(mario);

		marioObj->GetPosition(marioX, marioY);
		if (this->x < marioX)
		{
			aniId = ID_ANI_PTOOIE_RED_RIGHT;
		}
		else
		{
			aniId = ID_ANI_PTOOIE_RED_LEFT;
		}
		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
		//RenderBoundingBox();
	};

	virtual int IsCollidable() { return isCollidable; };
	virtual int IsBlocking() { return 0; }


	virtual void OnNoCollision(DWORD dt)
	{
		y += vy * dt;
	};


	virtual void OnCollisionWith(LPCOLLISIONEVENT e)
	{
	};

public:
	CPtooie(float x, float y, CGameObject* mario)
	{
		this->x = x;
		this->y = y;
		this->mario = mario;
		targetY = y - PTOOIE_BBOX_HEIGHT;
		retractY = y;
		lastMoveTime = GetTickCount64();
		SetCollidable(true);
		SetState(PTOOIE_STATE_RETRACT);
	}


	virtual void SetState(int state)
	{
		CGameObject::SetState(state);
		this->state = state;
		lastMoveTime = GetTickCount64(); 
		if (state == PTOOIE_STATE_RETRACT)
		{
			if (y < retractY)
			{
				vy = PTOOIE_SPEED;
			}
			else
			{
				vy = 0;
				if (y > retractY)
				{
					y = retractY;
				}
			}
		}
		else
		{
			if (y > targetY)
			{
				vy = -PTOOIE_SPEED;
			}
			else
			{
				vy = 0;
				if (y < targetY)
				{
					y = targetY;
				}
			}
		}
	};
};