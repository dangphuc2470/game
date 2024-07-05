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
#include "Landscape/Teleport.h"
#define KOOPA_SPEED_FROM_MARIO_SPEED_MULTIPLER -5.0f

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//ULONGLONG running = GetTickCount64();
	//Debug out title the time
	//DebugOutTitle(L"Time: %d", running_start - running);
	//DebugOutTitle(L"Ready to hold: %d", GetReadyToHold());
	//DebugOutTitle(L"Running: %d", running_start);
	//Debug out the position

	if (isFallingSlow && vy > -0.2) 
	{
		ay = MARIO_GRAVITY / 10;
	}


	if (y > 2000 && die_start == -1) // Mario die
	{
		x = 4000;
		die_start = GetTickCount64();
		return;
	}

	if (die_start != -1 && GetTickCount64() - die_start > 1000)
	{
			die_start = -1;
			if (GetLive() == 0)
			{
				CGame::GetInstance()->InitiateSwitchScene(5); // Reset game
				SetCoin(0);
				SetPoint(0);
				SetLive(4);
			}
			else
			AddLive( -1);
			CGame::GetInstance()->InitiateSwitchScene(5);
		// Change world
		return;
	}

	if (isSpinning && GetTickCount64() - spinning_start > MARIO_SPINNING_TIME)
	{
		isSpinning = false;
		spinning_start = -1;
	}

	if (time_remaining == 0)
	{
		SetState(MARIO_STATE_DIE);
	}

	//DebugOutTitle(L"Mario position: %f, %f", x, y);
	if (one_second_count && GetTickCount64() - one_second_count > 1000)
	{
		one_second_count = GetTickCount64();
		if (isNoCountDown)
			return;
		time_remaining--;
	}

	if (untouchable && GetTickCount64() - last_invisible_time > MARIO_UNTOUCHABLE_BLINK_TIME)
	{
		last_invisible_time = GetTickCount64();
		renderInvisibleSprite = !renderInvisibleSprite;
	}

	if (isGetDownPipe)
	{
		if (GetTickCount64() - getDownPipeStart > MARIO_PIPE_TIME)
		{
			isGetDownPipe = false;
			SetPosition(targetX, targetY);
		}
		else
			vy = MARIO_PIPE_SPEED * dt;

		CCollision::GetInstance()->Process(this, dt, coObjects);
		return;
	}

	if (isGetUpPipe)
		{
		if (GetTickCount64() - getUpPipeStart > MARIO_PIPE_TIME)
		{
			isGetUpPipe = false;
			SetPosition(targetX, targetY);
		}
		else
			vy = -MARIO_PIPE_SPEED * dt;

		CCollision::GetInstance()->Process(this, dt, coObjects);
		return;
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
					koopa->SetState(KOOPA_STATE_DIE_SLIP, static_cast<int> (vx * KOOPA_SPEED_FROM_MARIO_SPEED_MULTIPLER));
				StartUntouchable(true, true);
			}
			SetHoldingObject(NULL);
		}
	}
	vy += ay * dt;
	vx += ax * dt;

	float thisVx, thisVy;
	GetSpeed(thisVx, thisVy);
	//DebugOutTitle(L"Vx: %f, Vy: %f", thisVx, thisVy);
	if (((thisVx >= MARIO_RUNNING_SPEED || thisVx <= -MARIO_RUNNING_SPEED) && thisVy > 0) || isFlying)
	{
		if (running_start == -1)
			running_start = GetTickCount64();

		if (running_start && GetTickCount64() - running_start > MARIO_INCREASE_RUNNING_COUNT_TIME)
		{
			running_start = GetTickCount64();
			if (running_count < MAX_STAMITA)
			running_count++;
		}
	}
	else
	{
		if (running_start && GetTickCount64() - running_start > MARIO_DECREASE_RUNNING_COUNT_TIME)
		{
			running_start = GetTickCount64();
			if (running_count > 0)
				running_count--;
		}
	}
	if (isFlying)
	{
		if (GetTickCount64() - fly_start > MARIO_FLY_TIME)
		{
			isFlying = false;
			running_count = 2;
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
	SetIsOnPlatform(false);


	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	SetGravity(MARIO_GRAVITY);
	isFallingSlow = false;
	// Collison with object that is not collidable
	if (dynamic_cast<CGuideObject*>(e->obj))
	{
		return;
	}
	if (dynamic_cast<CTeleport*>(e->obj))
	{
		OnCollisionWithTeleport(e);
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

	if (dynamic_cast<CLeaf*>(e->obj))
	{
		OnCollisionWithLeaf(e);
		return;
	}
	
	// Collision with object that is collidable
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
			SetIsOnPlatform(true);
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
	{
	//	OnCollisionWithTheVoid(e);
	}
	else if (dynamic_cast<CBrick*>(e->obj))
	{
		if (e->ny > 0 && level != MARIO_LEVEL_SMALL)
			e->obj->SetState(BRICK_STATE_BROKEN);
	}
	else if (dynamic_cast<CMysteryBox*>(e->obj))
	{
		if (e->ny > 0)
		{
			if (e->obj->GetState() == MBOX_STATE_NORMAL)
			{
				e->obj->SetState(MBOX_STATE_UNBOX);
				AddPoint(100);
				AddCoin(1);
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
		OnCollisionWithMushroom(e);
	}
	else if (dynamic_cast<CVerticalPipe*>(e->obj))
	{
		
		CVerticalPipe* pipe = dynamic_cast<CVerticalPipe*>(e->obj);
		if (pipe->GetIsGetDownAble() && isSitting)
		{
			DebugOutTitle(L"Sitting");
			pipe->BlockFor1s();
		}
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
			AppearPoint(100);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (goomba->GetState() == GOOMBA_STATE_FLYING_NO_WINGS)
		{
			goomba->SetState(GOOMBA_STATE_FLYING_DIE);
			AppearPoint(100);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else
		{
			goomba->SetState(GOOMBA_STATE_FLYING_NO_WINGS);
			AppearPoint(100);
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
		if (button->GetState() == BUTTON_STATE_NORMAL && button->GetIsPressable())
		{
			button->SetState(BUTTON_STATE_PRESSED);
			CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
			scene->TurnBrickIntoCoin();
			scene->ShakeCamera();
		}
	}



}

void CMario::OnCollisionWithTeleport(LPCOLLISIONEVENT e)
{
	CTeleport* teleport = dynamic_cast<CTeleport*>(e->obj);
	teleport->GetTarget(targetX, targetY);
	if (e-> ny > 0)
		GetUpPipe();
	else
		GetDownPipe();
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
			AppearPoint(100);
			stateToSet = KOOPA_STATE_DIE;
			break;

		case KOOPA_STATE_WALKING:
			stateToSet = KOOPA_STATE_DIE;
			AppearPoint(100);

			break;

		case KOOPA_STATE_FLY:
			stateToSet = KOOPA_STATE_WALKING;
			AppearPoint(100);
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
					koopa->SetState(KOOPA_STATE_DIE_SLIP, static_cast<int>(e->nx));
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
	AddCoin(1);
	AddPoint(100);
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//void CMario::OnCollisionWithTheVoid(LPCOLLISIONEVENT e)
//{
//	DebugOut(L">>> Mario VOID >>> \n");
//	CBlackBackground* p = (CBlackBackground*)e->obj;
//	//SetState(MARIO_STATE_DIE);
//	//Todo: Go Die
//	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
//}

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

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	float ny = e->ny;
	float nx = e->nx;

	if (mushroom->GetState() == MUSHROOM_STATE_IDLE)
	{
		if (e->ny > 0)
			mushroom->SetState(MUSHROOM_STATE_MOVING_UP);
	}
	else if (mushroom->GetState() == MUSHROOM_STATE_WALKING)
	{
		if (level == MARIO_LEVEL_SMALL)
		{
			if (mushroom->IsRed())
			{
				SetLevel(MARIO_LEVEL_BIG);
				mushroom->SetState(MUSHROOM_STATE_POINT);
				SetPoint(GetPoint() + 1000);
			}
			else
			{
				mushroom->SetState(MUSHROOM_STATE_POINT);
				AddLive(1);
				SetPoint(GetPoint() + 1000);
			}
		}
		else
		{
			if (!mushroom->IsRed())
				AddLive(1);
			mushroom->SetState(MUSHROOM_STATE_POINT);
			SetPoint(GetPoint() + 1000);
		}
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
	float ny = e->ny;
	float nx = e->nx;

	if (leaf->GetState() == LEAF_STATE_IDLE)
	{
		if (e->ny > 0)
		{
			if (level == MARIO_LEVEL_SMALL)
				leaf->ChangeToMushroom();
			else
				leaf->SetState(LEAF_STATE_MOVING_UP);
		}
	}
	else if (leaf->GetState() == LEAF_STATE_FALLING)
	{
		if (level == MARIO_LEVEL_BIG)
		{
			SetLevel(MARIO_LEVEL_RACOON);
			leaf->SetState(LEAF_STATE_POINT);
			SetPoint(GetPoint() + 1000);

		}
		else
		{
			leaf->SetState(LEAF_STATE_POINT);
			SetPoint(GetPoint() + 1000);

		}
	}
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

	if (untouchable && GetTickCount64() - untouchable_start < MARIO_BOOM_TIME && !noBoom)
	{
		CAnimations::GetInstance()->Get(ID_ANI_MARIO_BOOM)->Render(x, y);
		return;
	}

	ULONGLONG elapsedSpinningTime = GetTickCount64() - spinning_start;
	if (isSpinning && elapsedSpinningTime < MARIO_SPINNING_TIME)
	{
		ULONGLONG interval = MARIO_SPINNING_TIME / 3;
		// Debugout the spinning time
		int spriteID = 0;
		if (elapsedSpinningTime <= interval) {
			spriteID = ID_SPRITE_MARIO_SPINNING_FRONT;
		}
		else if (elapsedSpinningTime <= interval * 2) {
			if (isFacingRight)
				spriteID = ID_SPRITE_MARIO_RACOON_IDLE_LEFT;
			else
				spriteID = ID_SPRITE_MARIO_RACOON_IDLE_RIGHT;
		}
		else {
			spriteID = ID_SPRITE_MARIO_SPINNING_BACK;
		}
		CSprites::GetInstance()->Get(spriteID)->Draw(x, y);
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

	//RenderBoundingBox();

	//DebugOutTitle(L"Coins: %d", coin);
}

void CMario::StartSpinning()
{
	DebugOutTitle(L"Start spinning");

	float fireball_Speed = MARIO_FIREBALL_SPEED;
	float fireball_X;
	if (isFacingRight)
	{
		fireball_X = x;
	}
	else
	{
		fireball_Speed = -fireball_Speed;
		fireball_X = x;
	}
	/*CGameObject* newObj = new CFireBall(x, y, fireball_Speed, 0, this);*/
	CGameObject* newObj = new CFireballnew(x, y, fireball_Speed, 0);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	newObj->SetPosition(fireball_X, y);
	scene->AddObject(newObj);

	if (isSpinning)
		return;
	isSpinning = true;
	spinning_start = GetTickCount64();
}

//void CMario::SetGuideObject()
//{
//
//
//	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
//	scene->AddObject(guideObject);
//}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE)
	{
		return;
	}

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
		else if (level == MARIO_LEVEL_RACOON)
		{
			isFallingSlow = true;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) 
		{
			if (level != MARIO_LEVEL_RACOON)
				vy += MARIO_JUMP_SPEED_Y / 2;

		}


		if (level != MARIO_LEVEL_RACOON)
			ay = MARIO_GRAVITY;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0;
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
void CMario::AppearPoint(int pointNum)
{
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	CPoint* point = new CPoint(x, y, pointNum);
	scene->AddObject(point);
	AddPoint(pointNum);
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
	StartUntouchable(true, false);
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
		y -= (MARIO_RACOON_BBOX_HEIGHT - MARIO_BIG_BBOX_HEIGHT) / 2  + 2;
		//x -= (MARIO_RACOON_BBOX_WIDTH - MARIO_BIG_BBOX_WIDTH) / 2;
	}

	level = l;
}

