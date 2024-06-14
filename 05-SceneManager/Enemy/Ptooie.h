//#pragma once
//#pragma once
//#include "../GameObject/GameObject.h"
//#include "../GameObject/AssetIDs.h"
//
//#define PTOOIE_GRAVITY 0.001f
//#define PTOOIE_WALKING_SPEED 0.05f
//
//
//#define PTOOIE_BBOX_WIDTH 16
//#define PTOOIE_BBOX_HEIGHT 15
//
//#define PTOOIE_STATE_WALKING 100
//#define PTOOIE_STATE_DIE 200
//#define PTOOIE_STATE_FLYING_WALK 300
//#define PTOOIE_STATE_FLYING_FLY 400
//#define PTOOIE_STATE_FLYING_NO_WINGS 500
//#define PTOOIE_STATE_FLYING_DIE 600
//#define PTOOIE_STATE_CHANGE_TIME_SHORT 100 //ms
//#define PTOOIE_STATE_CHANGE_TIME_LONG 2000 //ms
//
//
//class CPtooie : public CGameObject
//{
//protected:
//	float ax;
//	float ay;
//	DWORD lastStateChange;
//
//	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom)
//	{
//		switch (state)
//		{
//		case PTOOIE_STATE_DIE:
//			left = x - PTOOIE_BBOX_WIDTH / 2;
//			top = y - PTOOIE_BBOX_HEIGHT_DIE / 2;
//			right = left + PTOOIE_BBOX_WIDTH;
//			bottom = top + PTOOIE_BBOX_HEIGHT_DIE;
//			break;
//		
//		default:
//			DebugOutTitle(L"[ERROR] CPTOOIE::GetBoundingBox unknown state: %d\n", state);
//		}
//
//	}
//
//	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//	{
//		vy += ay * dt;
//		vx += ax * dt;
//
//		if ((state == PTOOIE_STATE_DIE || state == PTOOIE_STATE_FLYING_DIE) && (GetTickCount64() - die_start > PTOOIE_DIE_TIMEOUT))
//		{
//			isDeleted = true;
//			return;
//		}
//
//		DWORD now = GetTickCount64();
//		if (state == PTOOIE_STATE_FLYING_WALK || state == PTOOIE_STATE_FLYING_FLY)
//		{
//			DWORD changeTime = flyWalkTimes[flyWalkCycle % 8];
//			if (flyWalkCycle % 8 == 6)
//				PTOOIE_JUMP_SPEED = 0.25f;
//			else
//				PTOOIE_JUMP_SPEED = 0.1f;
//			if (now - lastStateChange >= changeTime)
//			{
//				if (state == PTOOIE_STATE_FLYING_WALK)
//					SetState(PTOOIE_STATE_FLYING_FLY);
//				else if (state == PTOOIE_STATE_FLYING_FLY)
//					SetState(PTOOIE_STATE_FLYING_WALK);
//
//				lastStateChange = now;
//				flyWalkCycle = (flyWalkCycle + 1) % 8;
//			}
//		}
//
//		//DebugOutTitle(L"[INFO] CPTOOIE::Update state: %d\n", state);
//		CGameObject::Update(dt, coObjects);
//		CCollision::GetInstance()->Process(this, dt, coObjects);
//	};
//
//
//	virtual void Render()
//	{
//		int aniId;
//		switch (state)
//		{
//		case PTOOIE_STATE_DIE:
//			aniId = ID_ANI_PTOOIE_DIE;
//			break;
//		case PTOOIE_STATE_FLYING_DIE:
//			aniId = ID_ANI_PTOOIE_FLY_DIE;
//			break;
//		case PTOOIE_STATE_FLYING_WALK:
//			aniId = ID_ANI_PTOOIE_FLY_WALK;
//			break;
//		case PTOOIE_STATE_FLYING_FLY:
//			aniId = ID_ANI_PTOOIE_FLY_FLY;
//			break;
//		case PTOOIE_STATE_FLYING_NO_WINGS:
//			aniId = ID_ANI_PTOOIE_FLY_NO_WINGS;
//			break;
//		default:
//			aniId = ID_ANI_PTOOIE_WALKING;
//			break;
//		}
//
//		CAnimations::GetInstance()->Get(aniId)->Render(x, y);
//		//RenderBoundingBox();
//	};
//
//	virtual int IsCollidable() { return isCollidable; };
//	virtual int IsBlocking() { return 0; }
//
//
//	virtual void OnNoCollision(DWORD dt)
//	{
//		x += vx * dt;
//		y += vy * dt;
//	};
//
//
//	virtual void OnCollisionWith(LPCOLLISIONEVENT e)
//	{
//		if (!e->obj->IsBlocking()) return;
//		if (dynamic_cast<CPTOOIE*>(e->obj)) return;
//
//		if (e->ny != 0)
//		{
//			vy = 0;
//		}
//		else if (e->nx != 0)
//		{
//			vx = -vx;
//		}
//
//	};
//
//public:
//	CPTOOIE(float x, float y, bool isHaveWing = 0)
//	{
//		this->ax = 0;
//		this->ay = PTOOIE_GRAVITY;
//		die_start = -1;
//		isHaveWing == 0 ?
//			SetState(PTOOIE_STATE_WALKING) :
//			SetState(PTOOIE_STATE_FLYING_WALK);
//		lastStateChange = GetTickCount64();
//		flyWalkCycle = 0;
//		CGameObject::SetCollidable(true);
//	}
//
//
//	virtual void SetState(int state)
//	{
//		CGameObject::SetState(state);
//		switch (state)
//		{
//		case PTOOIE_STATE_DIE:
//			die_start = GetTickCount64();
//			y += (PTOOIE_BBOX_HEIGHT - PTOOIE_BBOX_HEIGHT_DIE) / 2;
//			vx = 0;
//			vy = 0;
//			ay = 0;
//			break;
//		case PTOOIE_STATE_FLYING_DIE:
//			die_start = GetTickCount64();
//			y += (PTOOIE_BBOX_HEIGHT_FLY_WALK - PTOOIE_BBOX_HEIGHT_DIE) / 2;
//			vx = 0;
//			vy = 0;
//			ay = 0;
//			break;
//		case PTOOIE_STATE_WALKING:
//			vx = -PTOOIE_WALKING_SPEED;
//			break;
//		case PTOOIE_STATE_FLYING_WALK:
//			if (vx == 0)
//				vx = -PTOOIE_WALKING_SPEED;
//			break;
//		case PTOOIE_STATE_FLYING_FLY:
//			vy = -PTOOIE_JUMP_SPEED;
//			break;
//		case PTOOIE_STATE_FLYING_NO_WINGS:
//			break;
//		}
//	};
//};
//
