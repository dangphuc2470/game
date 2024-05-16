#include "Goomba.h"
#include "debug.h"
CGoomba::CGoomba(float x, float y, bool isHaveWings) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	if (isHaveWings)
		thisState = GOOMBA_STATE_WING1;
	else
		thisState = GOOMBA_STATE_WALKING;
	this->state = thisState;
	SetState(thisState);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (thisState == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else if (thisState = GOOMBA_STATE_WALKING)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
	else
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_WINGS;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((thisState == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	DebugOut(L"[TEST] Goomba render %d\n", thisState);

	int aniId = ID_ANI_GOOMBA_WING1;
	switch (thisState)
	{
	case GOOMBA_STATE_DIE:
		aniId = ID_ANI_GOOMBA_DIE;
		break;
	case GOOMBA_STATE_WING1:
		aniId = ID_ANI_GOOMBA_WING1;
		break;
	case GOOMBA_STATE_WING2:
		aniId = ID_ANI_GOOMBA_WING2;
		break;
	case GOOMBA_STATE_WALKING:
		aniId = ID_ANI_GOOMBA_WALKING;
		break;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += 100;//(GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_WING1:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_WING2:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	}
}
