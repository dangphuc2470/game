#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
#include "../Enemy/GuideObject.h"
#include "../Scene/PlayScene.h"
#include "../Enemy/Goomba.h"

#define KOOPA_GRAVITY 0.001f
#define KOOPA_WALKING_SPEED 0.05f
#define KOOPA_SLIP_SPEED 0.2f
#define KOOPA_STATE_CHANGE_JUMP 0.1f


#define KOOPA_BBOX_WIDTH 15
#define KOOPA_BBOX_HEIGHT 25
#define KOOPA_BBOX_HEIGHT_WINGS 26
#define KOOPA_BBOX_HEIGHT_DIE 15
#define KOOPA_JUMP_SPEED 0.3f
#define KOOPA_JUMP_INTERVAL 1000
#define KOOPA_DIE_TIMEOUT 5000
#define KOOPA_FLASH_TIME 3000

#define KOOPA_STATE_WALKING 100
#define KOOPA_STATE_DIE 200
#define KOOPA_STATE_DIE_SLIP 201
#define KOOPA_STATE_FLY 300
#define KOOPA_STATE_FLASH 700
#define KOOPA_DELETE_TIME 5000

#define GUIDE_AND_KOOPA_POSITION_Y_TOLERANCE 3 // If the distance between guide and koopa is greater than 3 pixel, the koopa is considered falling

class CKoopa : public CGameObject
{
protected:
	//Todo: Improve Koopa flash animation
	float ax;
	float ay;
	int previousState = -1;
	CGuideObject* guide;
	DWORD lastJumpTime;
	DWORD dieStartTime;
	DWORD respawnStartTime;
	DWORD deleteStartTime;
	string color;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		if (state == KOOPA_STATE_DIE ||
			state == KOOPA_STATE_DIE_SLIP || state == KOOPA_STATE_FLASH)
		{
			top = y - KOOPA_BBOX_HEIGHT_DIE / 2;
			right = left + KOOPA_BBOX_WIDTH;
			bottom = top + KOOPA_BBOX_HEIGHT_DIE;
		}
		else if (state == KOOPA_STATE_FLY)
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

	void SetColliable(bool isColliable)
	{
		CGameObject::SetCollidable(isColliable);
		if (!isColliable)
			deleteStartTime = GetTickCount64();
	}

	void SetColor(string color)
	{
		this->color = color;
	}

	string GetColor()
	{
		return color;
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		vy += ay * dt;
		vx += ax * dt;

		if (IsFalling() && (state == KOOPA_STATE_WALKING))
			ChangeDirection();

		DWORD now = GetTickCount64();
		if (!isCollidable && now - deleteStartTime > KOOPA_DELETE_TIME)
		{
			isDeleted = true;
			guide->isDeleted = true;
		}


		if ((state == KOOPA_STATE_FLY) && now - lastJumpTime >= KOOPA_JUMP_INTERVAL)
		{
			vy = -KOOPA_JUMP_SPEED; // Make Koopa jump
			lastJumpTime = now;
		}

		else if (state == KOOPA_STATE_DIE && GetTickCount64() - dieStartTime > KOOPA_DIE_TIMEOUT)
		{
			SetState(KOOPA_STATE_FLASH);
		}
		else if ((state == KOOPA_STATE_FLASH) && GetTickCount64() - dieStartTime > KOOPA_FLASH_TIME)
		{
			SetState(KOOPA_STATE_WALKING);
		}
		else {
			//throw L"Koopa State Error";
		}



		//DebugOutTitle(L"[INFO] Koopa y: %f\n", y);

		//guide->Update(dt, coObjects);
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	};
	virtual void Render()
	{
		 if (state == KOOPA_STATE_DIE)
		{
			if (color == "green")
				CSprites::GetInstance()->Get(ID_SPRITE_KOOPA_DIE_GREEN + 3)->Draw(x, y);
			else
				CSprites::GetInstance()->Get(ID_SPRITE_KOOPA_DIE_RED + 3)->Draw(x, y);
		}
		else
		{
			int aniID = KOOPA_STATE_WALKING;
			switch (state)
			{
			case KOOPA_STATE_WALKING:
				if (color == "green")
					vx > 0 ? aniID = ID_ANI_KOOPA_WALKING_GREEN_RIGHT : aniID = ID_ANI_KOOPA_WALKING_GREEN_LEFT;
				else
					vx > 0 ? aniID = ID_ANI_KOOPA_WALKING_RED_RIGHT : aniID = ID_ANI_KOOPA_WALKING_RED_LEFT;
				break;
			case KOOPA_STATE_DIE_SLIP:
				if (color == "green")
					aniID = ID_ANI_KOOPA_DIE_GREEN;
				else
					aniID = ID_ANI_KOOPA_DIE_RED;
				break;
			case KOOPA_STATE_FLY:
				if (color == "green")
				vx > 0 ? aniID = ID_ANI_KOOPA_FLY_GREEN_RIGHT : aniID = ID_ANI_KOOPA_FLY_GREEN_LEFT;
				else 
					vx > 0 ? aniID = ID_ANI_KOOPA_FLY_RED_RIGHT : aniID = ID_ANI_KOOPA_FLY_RED_LEFT;
				break;
			

			case KOOPA_STATE_FLASH:
				if (color == "green")
					aniID = ID_ANI_KOOPA_FLASH_GREEN;
				else
					aniID = ID_ANI_KOOPA_FLASH_RED;
				break;
		
			default:
				DebugOutTitle(L"[INFO] Koopa State Error: %d\n", state);
				break;
			}
			CAnimations::GetInstance()->Get(aniID)->Render(x, y);
		}
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
		//
		if (dynamic_cast<CKoopa*>(e->obj))
		{
			DebugOutTitle(L"[INFO] Koopa Collision with Koopa\n");
			if (this->state == KOOPA_STATE_DIE_SLIP)
			{
				CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

				koopa->SetState(KOOPA_STATE_DIE);
				koopa->SetColliable(false);
				//koopa->isDeleted = true;
			}
			return;
		}
		else if (dynamic_cast<CGoomba*>(e->obj) && (this->state == KOOPA_STATE_DIE_SLIP))
		{
			CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
			//goomba->SetState(GOOMBA_STATE_DIE);
			goomba->SetCollidable(false);
		}

		if (!e->obj->IsBlocking()) return;
		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
			ChangeDirection();
	};

public:
	CKoopa(float x, float y, bool isGreen = false, bool isHaveWings = false)
	{
		this->ax = 0;
		this->ay = KOOPA_GRAVITY;
		if (isGreen)
			this->color = "green";
		else
			this->color = "red";

		if (isHaveWings)
			SetState(KOOPA_STATE_FLY);
		else
			SetState(KOOPA_STATE_WALKING);

		lastJumpTime = GetTickCount64();
		guide = new CGuideObject(this);
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		guide->SetPosition(x + KOOPA_BBOX_WIDTH, y);
		scene->AddObject(guide);
		SetColliable(true);
	};


	virtual void SetState(int state, int nx = 1)
	{
		//DebugOutTitle(L"[INFO] Koopa SetState: %d\n", state);

		CGameObject::SetState(state);
		switch (state)
		{
		case KOOPA_STATE_WALKING:
			vy = -KOOPA_STATE_CHANGE_JUMP;
			vx = KOOPA_WALKING_SPEED;
			if (previousState == KOOPA_STATE_FLY)
				y -= (KOOPA_BBOX_HEIGHT_WINGS - KOOPA_BBOX_HEIGHT);
			break;
		case KOOPA_STATE_DIE:
			dieStartTime = GetTickCount64();
			vy = -KOOPA_STATE_CHANGE_JUMP;
			vx = 0;
			if (previousState == KOOPA_STATE_WALKING)				// If previous state is walking, move the koopa up a bit so it doesn't fall through the ground, if already died, no need
				y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
			y = floor(y);
			break;

		case KOOPA_STATE_DIE_SLIP:
			vy = -KOOPA_STATE_CHANGE_JUMP;
			vx = KOOPA_SLIP_SPEED * -nx;
			break;


		case KOOPA_STATE_FLY:
			vy = -KOOPA_STATE_CHANGE_JUMP;
			vx = KOOPA_WALKING_SPEED;
			break;

		case KOOPA_STATE_FLASH:
			dieStartTime = GetTickCount64();
			vx = 0;
			vy = 0;
			break;
		default:
			DebugOutTitle(L"[INFO] Koopa SetState Error: %d\n", state);
			break;
		}
		//show speed
		previousState = state;

	}

	void GetPosition(float& x, float& y)
	{
		x = this->x;
		y = this->y;
	}

	bool IsFalling()
	{
		float gx, gy;
		guide->GetPosition(gx, gy);
		//DebugOutTitle(L"Guide Position: %f %f, Koopa Position: %f, %f", gx, gy, x, y);
		if (abs(gy - y) > GUIDE_AND_KOOPA_POSITION_Y_TOLERANCE)
			return true;
		return false;
	}

	void ChangeDirection()
	{
		vx = -vx;
		if (vx > 0)
			guide->SetPosition(x + KOOPA_BBOX_WIDTH, y);
		else
			guide->SetPosition(x - KOOPA_BBOX_WIDTH, y);
	}

};