#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
#include "../Enemy/GuideObject.h"
#include "../Scene/PlayScene.h"

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
#define KOOPA_DIE_TIMEOUT 500

#define KOOPA_STATE_WALKING_GREEN 100
#define KOOPA_STATE_DIE_GREEN 200
#define KOOPA_STATE_DIE_SLIP_GREEN 201
#define KOOPA_STATE_FLY_GREEN 300
#define KOOPA_STATE_WALKING_RED 400
#define KOOPA_STATE_DIE_RED 500
#define KOOPA_STATE_DIE_SLIP_RED 501
#define KOOPA_STATE_FLY_RED 600

#define GUIDE_AND_KOOPA_POSITION_Y_TOLERANCE 3 // If the distance between guide and koopa is greater than 3 pixel, the koopa is considered falling

class CKoopa : public CGameObject
{
protected:
	float ax;
	float ay;
	int previousState = -1;
	CGuideObject* guide;
	DWORD lastJumpTime;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
	{
		left = x - KOOPA_BBOX_WIDTH / 2;
		if (state == KOOPA_STATE_DIE_GREEN || state == KOOPA_STATE_DIE_RED || state == KOOPA_STATE_DIE_SLIP_RED || state == KOOPA_STATE_DIE_SLIP_GREEN)
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

		if (IsFalling() && (state == KOOPA_STATE_WALKING_GREEN || state == KOOPA_STATE_WALKING_RED))
			ChangeDirection();


		DWORD now = GetTickCount64();

		if ((state == KOOPA_STATE_FLY_GREEN || state == KOOPA_STATE_FLY_RED) && now - lastJumpTime >= KOOPA_JUMP_INTERVAL)
		{
			vy = -KOOPA_JUMP_SPEED; // Make Koopa jump
			lastJumpTime = now;
		}
		//DebugOutTitle(L"[INFO] Koopa y: %f\n", y);
		
		//guide->Update(dt, coObjects);
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	};
	virtual void Render()
	{
		if (state == KOOPA_STATE_DIE_RED)
		{
			CSprites::GetInstance()->Get(ID_SPRITE_KOOPA_DIE_RED + 3)->Draw(x, y);
		}
		else if (state == KOOPA_STATE_DIE_GREEN)
		{
			CSprites::GetInstance()->Get(ID_SPRITE_KOOPA_DIE_GREEN + 3 )->Draw(x, y);
		}
		else
		{
			int aniID = KOOPA_STATE_WALKING_GREEN;
			switch (state)
			{
			case KOOPA_STATE_WALKING_GREEN:
				vx > 0 ? aniID = ID_ANI_KOOPA_WALKING_GREEN_RIGHT : aniID = ID_ANI_KOOPA_WALKING_GREEN_LEFT;
				break;
			case KOOPA_STATE_DIE_SLIP_GREEN:
				aniID = ID_ANI_KOOPA_DIE_GREEN;
				break;
			case KOOPA_STATE_FLY_GREEN:
				vx > 0 ? aniID = ID_ANI_KOOPA_FLY_GREEN_RIGHT : aniID = ID_ANI_KOOPA_FLY_GREEN_LEFT;
				break;
			case KOOPA_STATE_WALKING_RED:
				vx > 0 ? aniID = ID_ANI_KOOPA_WALKING_RED_RIGHT : aniID = ID_ANI_KOOPA_WALKING_RED_LEFT;
				break;
			case KOOPA_STATE_DIE_SLIP_RED:
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
		}
		//RenderBoundingBox();
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
			ChangeDirection();
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
		lastJumpTime = GetTickCount64();
		guide = new CGuideObject(this);
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		guide->SetPosition(x + KOOPA_BBOX_WIDTH, y);
		scene->AddObject(guide);

	};


	virtual void SetState(int state, int nx = 1)
	{
		//DebugOutTitle(L"[INFO] Koopa SetState: %d\n", state);

		CGameObject::SetState(state);
		switch (state)
		{
		case KOOPA_STATE_WALKING_GREEN:
			vy = -KOOPA_STATE_CHANGE_JUMP;
			vx = KOOPA_WALKING_SPEED;
			if (previousState == KOOPA_STATE_FLY_GREEN)
				y -= (KOOPA_BBOX_HEIGHT_WINGS - KOOPA_BBOX_HEIGHT);
			break;

		case KOOPA_STATE_WALKING_RED:
			vx = KOOPA_WALKING_SPEED;
			vy = -KOOPA_STATE_CHANGE_JUMP;
			if (previousState == KOOPA_STATE_FLY_RED)
				y -= (KOOPA_BBOX_HEIGHT_WINGS - KOOPA_BBOX_HEIGHT) ;
			break;

		case KOOPA_STATE_DIE_GREEN:
			vy = -KOOPA_STATE_CHANGE_JUMP;
			vx = 0;
			if (previousState == KOOPA_STATE_WALKING_GREEN)				// If previous state is walking, move the koopa up a bit so it doesn't fall through the ground, if already died, no need
				y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
			y = floor(y);
			break;

		case KOOPA_STATE_DIE_RED:
			vx = 0;
			vy = -KOOPA_STATE_CHANGE_JUMP;
			if (previousState == KOOPA_STATE_WALKING_RED)				// If previous state is walking, move the koopa up a bit so it doesn't fall through the ground, if already died, no need
				y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE) / 2;
			y = floor(y);
			break;
		case KOOPA_STATE_DIE_SLIP_GREEN:
			vy = -KOOPA_STATE_CHANGE_JUMP;
			vx = KOOPA_SLIP_SPEED * -nx;
			break;
		
		case KOOPA_STATE_DIE_SLIP_RED:
			vx = KOOPA_SLIP_SPEED * -nx;
			vy = -KOOPA_STATE_CHANGE_JUMP;
			break;

		case KOOPA_STATE_FLY_GREEN:
			vy = -KOOPA_STATE_CHANGE_JUMP;
			vx = KOOPA_WALKING_SPEED;
			break;

		case KOOPA_STATE_FLY_RED:
			vx = KOOPA_WALKING_SPEED;
			vy = -KOOPA_STATE_CHANGE_JUMP;
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