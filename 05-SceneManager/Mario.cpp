#include <algorithm>
#include "../05-SceneManager/Game/debug.h"

#include "Mario.h"
#include "../05-SceneManager/Game/Game.h"

#include "../05-SceneManager/Enemy/Goomba.h"
#include "../05-SceneManager/Enemy/Ptooie.h"
#include "../05-SceneManager/Item/Coin.h"
#include "../05-SceneManager/Landscape/Portal.h"
#include "../05-SceneManager/Landscape/Background.h"
#include "../05-SceneManager/Landscape/Brick.h"
#include "../05-SceneManager/Landscape/MysteryBox.h"
#include "../05-SceneManager/Enemy/Koopa.h"
#include "../05-SceneManager/Enemy/FireBall.h"
#include "../05-SceneManager/Scene/PlayScene.h"

#include "../05-SceneManager/GameObject/Collision.h"
#include "Landscape/Spawner.h"
#include "Item/Button.h"
#define KOOPA_SPEED_FROM_MARIO_SPEED_MULTIPLER -5.0f

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//ULONGLONG running = GetTickCount64();
	//Debug out title the time
	//DebugOutTitle(L"Time: %d", running_start - running);
	//DebugOutTitle(L"Ready to hold: %d", GetReadyToHold());
	//DebugOutTitle(L"Running: %d", running_start);
	//DebugOutTitle(L"Mario position: %f, %f", x, y);

	if (untouchable && GetTickCount64() - last_invisible_time > MARIO_UNTOUCHABLE_BLINK_TIME)
	{
		last_invisible_time = GetTickCount64();
		renderInvisibleSprite = !renderInvisibleSprite;
	}
	if (holdingObject != NULL)
	{
		if (!GetReadyToHold())
		{
			if (dynamic_cast<CKoopa*>(holdingObject))
			{
				CKoopa* koopa = dynamic_cast<CKoopa*>(holdingObject);
				if (koopa->GetState() == KOOPA_STATE_FLASH)
				{
				}
				else if (vx == 0)
					koopa->SetState(KOOPA_STATE_DIE);
				else
					koopa->SetState(KOOPA_STATE_DIE_SLIP, vx * KOOPA_SPEED_FROM_MARIO_SPEED_MULTIPLER);
				StartUntouchable(true);
			}
			SetHoldingObject(NULL);
		}
	}
	vy += ay * dt;
	vx += ax * dt;
	if (isFlying)
	{
		if (GetTickCount64() - fly_start > MARIO_FLY_TIME)
		{
			isFlying = false;
			vy = 0;
		}
		else
			vy = -MARIO_FLY_SPEED * dt;
	}

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
		renderInvisibleSprite = false;
	}
	/*if (GetState() == MARIO_STATE_FLY && GetTickCount64() - fly_start > MARIO_FLY_TIME)
	{
		SetState(MARIO_STATE_IDLE);
	}*/
	isOnPlatform = false;


	CCollision::GetInstance()->Process(this, dt, coObjects);
	//DebugOutTitle(L"X: %f, Y: %f, VX: %f, VY: %f", x, y, vx, vy);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGuideObject*>(e->obj))
	{
		return;
	}
	if (dynamic_cast<CFireBall*>(e->obj))
	{
		OnCollisionWithFireball(e);
		return;
	}
	if (dynamic_cast<CButton*>(e->obj))
	{
		OnCollisionWithButton(e);
		return;
	}

	if (e->ny != 0 && e->obj->IsBlocking())
	{
		float x, y;
		e->obj->GetPositionTopBot(x, y);
		float t, b;
		this->GetPositionTopBot(t, b);
		x = floor(x);
		y = floor(y);
		t = floor(t);
		b = floor(b);

		//DebugOutTitle(L"Collision at %f %f, Mario %f %f", x, y, t, b);
		vy = 0;
		if (e->ny < 0) {
			isOnPlatform = true;
			//DebugOutTitle(L"On Platform\n");
		}
		//DebugOutTitle(L"Not on Platform\n");*/
		//Debug out title the ny, x, b
		//DebugOutTitle(L"ny: %f, x: %f, b: %f", e->ny, x, b);
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CKoopa*>(e->obj))
		OnCollisionWithKoopa(e);
	else if (dynamic_cast<CBlackBackground*>(e->obj))
		OnCollisionWithTheVoid(e);
	else if (dynamic_cast<CBrick*>(e->obj))
	{
		if (e->ny > 0)
			e->obj->SetState(BRICK_STATE_BROKEN);
	}
	else if (dynamic_cast<CMysteryBox*>(e->obj))
	{
		if (e->ny > 0)
		{
			if (e->obj->GetState() == MBOX_STATE_NORMAL)
			{
				e->obj->SetState(MBOX_STATE_UNBOX);
			}

		}
	}
	else if (dynamic_cast<CPtooie*>(e->obj))
	{
		OnCollisionWithPtooie(e);
	}

	else if (dynamic_cast<CSpawner*>(e->obj))
	{
		OnCollisionWithSpawner(e);
	}
	else if (dynamic_cast<CMushroom*>(e->obj))
	{
		CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
		mushroom->SetState(MUSHROOM_STATE_DIE);
		if (level == MARIO_LEVEL_SMALL)
			SetLevel(MARIO_LEVEL_BIG);
		else
			coin += 1000;
		return;
	}
	//DebugOutTitle(L"Collision at %f %f, Mario %f %f", x, y, top, bottom);
	/*else if (dynamic_cast<CGoombaFlying*>(e->obj))
		OnCollisionWithGoombaFlying(e);*/
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() == GOOMBA_STATE_DIE || goomba->GetState() == GOOMBA_STATE_FLYING_DIE)
			return;

		if (goomba->GetState() == GOOMBA_STATE_WALKING)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (goomba->GetState() == GOOMBA_STATE_FLYING_NO_WINGS)
		{
			goomba->SetState(GOOMBA_STATE_FLYING_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else
		{
			goomba->SetState(GOOMBA_STATE_FLYING_NO_WINGS);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE && goomba->GetState() != GOOMBA_STATE_FLYING_DIE)
			{
				MarioChangeSmallerLevel();
			}
		}
	}
}

void CMario::OnCollisionWithSpawner(LPCOLLISIONEVENT e)
{
	// Only spawn when go left to righ
	if (e->nx < 0)
	{
		CSpawner* spawner = dynamic_cast<CSpawner*>(e->obj);
		spawner->Spawn(this);
	}

}

void CMario::OnCollisionWithButton(LPCOLLISIONEVENT e)
{
	CButton* button = dynamic_cast<CButton*>(e->obj);
	if (e->ny > 0)
	{
		button->MoveUp();
	}
	else
	{
		if (button->GetState() == BUTTON_STATE_NORMAL)
		{
			button->SetState(BUTTON_STATE_PRESSED);
			CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
			scene->TurnBrickIntoCoin();
			scene->ShakeCamera();
		}
	}



}

void CMario::OnCollisionWithKoopa(LPCOLLISIONEVENT e)
{
	CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);

	// jump on top >> kill Koopa and deflect a bit 
	if (e->ny < 0)
	{
		int stateToSet = -1;
		switch (koopa->GetState())
		{
		case KOOPA_STATE_DIE:
			stateToSet = KOOPA_STATE_DIE_SLIP;
			break;

		case KOOPA_STATE_DIE_SLIP:
			stateToSet = KOOPA_STATE_DIE;
			break;

		case KOOPA_STATE_WALKING:
			stateToSet = KOOPA_STATE_DIE;
			break;

		case KOOPA_STATE_FLY:
			stateToSet = KOOPA_STATE_WALKING;
			break;

		}
		if (stateToSet != -1)
			koopa->SetState(stateToSet, -1);
		vy = -MARIO_JUMP_DEFLECT_SPEED;

	}
	else // hit by Koopa
	{
		if (untouchable == 0)
		{
			if (koopa->GetState() == KOOPA_STATE_DIE)
			{

				switch (state)
				{
				case MARIO_STATE_RUNNING_RIGHT:
					koopa->SetState(KOOPA_STATE_DIE_HOLD_RIGHT, this);
					SetHoldingObject(koopa);
					break;
				case MARIO_STATE_RUNNING_LEFT:
					koopa->SetState(KOOPA_STATE_DIE_HOLD_LEFT, this);
					SetHoldingObject(koopa);
					break;
				default:
					koopa->SetState(KOOPA_STATE_DIE_SLIP, e->nx);
					break;
				}


			}
			else if (holdingObject == NULL)
			{
				if (koopa->GetState() == KOOPA_STATE_DIE || koopa->GetState() == KOOPA_STATE_FLASH)
				{
					return;
				}
				MarioChangeSmallerLevel();
			}
		}
	}

}

void CMario::OnCollisionWithPtooie(LPCOLLISIONEVENT e)
{
	CPtooie* ptooie = dynamic_cast<CPtooie*>(e->obj);
	if (untouchable == 0)
	{
		float vx, vy;
		ptooie->GetSpeed(vx, vy);
		if (ptooie->GetState() == PTOOIE_STATE_RETRACT && vy == 0)
		{
			return;
		}
		MarioChangeSmallerLevel();
	}

}

void CMario::OnCollisionWithFireball(LPCOLLISIONEVENT e)
{
	CFireBall* fireball = dynamic_cast<CFireBall*>(e->obj);
}



void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithTheVoid(LPCOLLISIONEVENT e)
{
	DebugOut(L">>> Mario VOID >>> \n");
	CBlackBackground* p = (CBlackBackground*)e->obj;
	//SetState(MARIO_STATE_DIE);
	//Todo: Go Die
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID racoon Mario
//
int CMario::GetAniIdRacoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACOON_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_RACOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_RACOON_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACOON_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACOON_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_RACOON_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RACOON_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_RACOON_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACOON_IDLE_RIGHT;

	return aniId;
}


void CMario::Render()
{
	if (renderInvisibleSprite && GetTickCount64() - untouchable_start >= MARIO_BOOM_TIME && !noFlash)
	{
		CSprites::GetInstance()->Get(ID_SPRITE_MARIO_INVISIBLE)->Draw(x, y);
		return;
	}

	if (untouchable && GetTickCount64() - untouchable_start < MARIO_BOOM_TIME && !noFlash)
	{
		CAnimations::GetInstance()->Get(ID_ANI_MARIO_BOOM)->Render(x, y);
		return;
	}


	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIdRacoon();
	else
		DebugOutTitle(L"Invalid Mario level");

	//DebugOutTitle(L"Animation ID: %d", aniId);
	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();

	//DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	//DebugOutTitle(L"Set state %d", state);
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE)
		return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		if (holdingObject != NULL)
		{
			CKoopa* koopa = dynamic_cast<CKoopa*>(holdingObject);
			koopa->SetState(KOOPA_STATE_DIE_HOLD_RIGHT, this);
		}
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		//DebugOutTitle(L"Running");
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		if (holdingObject != NULL)
		{
			CKoopa* koopa = dynamic_cast<CKoopa*>(holdingObject);
			koopa->SetState(KOOPA_STATE_DIE_HOLD_LEFT, this);
		}
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		//DebugOutTitle(L"Runningl");
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		ay = MARIO_GRAVITY;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			if (level == MARIO_LEVEL_BIG)
				y += MARIO_SIT_HEIGHT_ADJUST;
			else if (level == MARIO_LEVEL_RACOON)
				y += MARIO_SIT_HEIGHT_ADJUST_RACOON;
			else
				throw("Invalid Mario level");
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			if (level == MARIO_LEVEL_BIG)
				y -= MARIO_SIT_HEIGHT_ADJUST;
			else if (level == MARIO_LEVEL_RACOON)
				y -= MARIO_SIT_HEIGHT_ADJUST_RACOON;
			else
				throw("Invalid Mario level");
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		//ay = MARIO_GRAVITY;
		//DebugOutTitle(L"Idle");
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;

	}


	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_RACOON)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_RACOON_BBOX_WIDTH / 2;
			top = y - MARIO_RACOON_BBOX_HEIGHT / 2;
			right = left + MARIO_RACOON_BBOX_WIDTH;
			bottom = top + MARIO_RACOON_BBOX_HEIGHT;
		}
	}
	else
		throw("Invalid Mario level");
	this->top = top;
	this->bottom = bottom;
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		if (l == MARIO_LEVEL_RACOON)
		{
			y -= (MARIO_RACOON_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
			//x -= (MARIO_RACOON_BBOX_WIDTH - MARIO_SMALL_BBOX_WIDTH) / 2;
		}
		else if (l == MARIO_LEVEL_BIG)
			y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	else if (this->level == MARIO_LEVEL_BIG && l == MARIO_LEVEL_RACOON)
	{
		y -= (MARIO_RACOON_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT) / 2;
		//x -= (MARIO_RACOON_BBOX_WIDTH - MARIO_BIG_BBOX_WIDTH) / 2;
	}

	level = l;
}

