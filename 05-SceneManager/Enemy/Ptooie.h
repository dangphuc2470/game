#pragma once
#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
#include "../Mario.h"
#include "./Fireball.h"
#include "../Scene/PlayScene.h"

#define PTOOIE_SPEED 0.05f

#define PTOOIE_BBOX_WIDTH 15
#define PTOOIE_BBOX_HEIGHT 31

#define PTOOIE_STATE_EXTEND 100
#define PTOOIE_STATE_RETRACT 200
#define PTOOIE_STATE_DIE 300
#define PTOOIE_DISTANCE_TO_EXTEND 200
#define PIPE_WIDTH 20
#define FIREBALL_SPEED 0.05f
#define NEXT_FIREBALL_TIME 3000
#define TIME_BETWEEN_STATE 3000
#define ID_SPRITE_PTOOIE_RED_LEFT_DOWN 5210
#define ID_SPRITE_PTOOIE_RED_LEFT_UP 5211
#define ID_SPRITE_PTOOIE_RED_RIGHT_UP 5212
#define ID_SPRITE_PTOOIE_RED_RIGHT_DOWN 5213


class CPtooie : public CGameObject
{
protected:
	bool isMovingUp = false;
	float targetY;
	float retractY; 
	DWORD lastMoveTime; 
	DWORD lastFireballTime;
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

		if (distance < PIPE_WIDTH || distance > PTOOIE_DISTANCE_TO_EXTEND)
		{
			//DebugOutTitle(L"Be hon");
			if (now - lastMoveTime > TIME_BETWEEN_STATE)
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
			if (y > targetY)
			{
				vy = -PTOOIE_SPEED;
			}
			else
			{
				if (now - lastFireballTime > NEXT_FIREBALL_TIME)
				{
					float vx, vy;
					CalculateFireballSpeed(x, y, marioX, marioY, vx, vy);
					CGameObject* newObj = new CFireBall(x, y, vx, vy, marioObj);
					CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
					newObj->SetPosition(x, y - 5);
					scene->AddObject(newObj);
					lastFireballTime = now;
				}

				vy = 0;
				if (y < targetY)
				{
					y = targetY;
				}
				if (now - lastMoveTime > TIME_BETWEEN_STATE)
					SetState(PTOOIE_STATE_RETRACT);
			}
		}
		else if (state == PTOOIE_STATE_RETRACT)
		{
			//DebugOutTitle(L"Lon hon");

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
				if (now - lastMoveTime > TIME_BETWEEN_STATE)
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
			//Mario right
			if (vy > 0)
				CSprites::GetInstance()->Get(ID_SPRITE_PTOOIE_RED_RIGHT_UP)->Draw(x, y);
			else
				CSprites::GetInstance()->Get(ID_SPRITE_PTOOIE_RED_RIGHT_DOWN)->Draw(x, y);
		}
		else
		{
			//Mario left
			if (vy > 0)
				CSprites::GetInstance()->Get(ID_SPRITE_PTOOIE_RED_LEFT_UP)->Draw(x, y);
			else
				CSprites::GetInstance()->Get(ID_SPRITE_PTOOIE_RED_LEFT_DOWN)->Draw(x, y);
		}
		//CAnimations::GetInstance()->Get(aniId)->Render(x, y);
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
		lastFireballTime = -1;
		SetCollidable(true);
		SetState(PTOOIE_STATE_RETRACT);

		
	}

	void CalculateFireballSpeed(float ptooieX, float ptooieY, float marioX, float marioY, float& vx, float& vy)
	{
		float fireballSpeed = 0.05f;
		float dirX = marioX - ptooieX;
		float dirY = marioY - ptooieY;

		// Calculate the distance from Ptooie to Mario
		float distance = sqrt(dirX * dirX + dirY * dirY);

		// Normalize the direction vector
		float normDirX = dirX / distance;
		float normDirY = dirY / distance;

		// Calculate the velocity of the fireball
		vx = normDirX * fireballSpeed + 0.01;
		vy = normDirY * fireballSpeed;
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

