//#include "Goomba.h"
//
//
//
//
//
//
//CGoombaFlying::CGoombaFlying(float x, float y) :CGameObject(x, y)
//{
//	this->ax = 0;
//	this->ay = GOOMBA_GRAVITY;
//	die_start = -1;
//	SetState(GOOMBA_STATE_WALKING);
//}
//
//void CGoombaFlying::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	if (state == GOOMBA_STATE_DIE)
//	{
//		left = x - GOOMBA_BBOX_WIDTH / 2;
//		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
//		right = left + GOOMBA_BBOX_WIDTH;
//		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
//	}
//	else
//	{
//		left = x - GOOMBA_BBOX_WIDTH / 2;
//		top = y - GOOMBA_BBOX_HEIGHT_FLY / 2;
//		right = left + GOOMBA_BBOX_WIDTH;
//		bottom = top + GOOMBA_BBOX_HEIGHT_FLY;
//	}
//}
//
//void CGoombaFlying::OnNoCollision(DWORD dt)
//{
//	x += vx * dt;
//	y += vy * dt;
//};
//
//void CGoombaFlying::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//	if (!e->obj->IsBlocking()) return;
//	if (dynamic_cast<CGoombaFlying*>(e->obj)) return;
//
//	if (e->ny != 0)
//	{
//		vy = 0;
//	}
//	else if (e->nx != 0)
//	{
//		vx = -vx;
//	}
//
//}
//
//void CGoombaFlying::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
//{
//	vy += ay * dt;
//	vx += ax * dt;
//
//	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
//	{
//		isDeleted = true;
//		return;
//	}
//
//	CGameObject::Update(dt, coObjects);
//	CCollision::GetInstance()->Process(this, dt, coObjects);
//}
//
//
//void CGoombaFlying::Render()
//{
//	int aniId = ID_ANI_GOOMBA_FLY_WALK;
//	if (state == GOOMBA_STATE_DIE)
//	{
//		aniId = ID_ANI_GOOMBA_DIE;
//	}
//
//	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
//	RenderBoundingBox();
//}
//
//void CGoombaFlying::SetState(int state)
//{
//	CGameObject::SetState(state);
//	switch (state)
//	{
//	case GOOMBA_STATE_DIE:
//		die_start = GetTickCount64();
//		y += (GOOMBA_BBOX_HEIGHT_FLY - GOOMBA_BBOX_HEIGHT_DIE) / 2;
//		vx = 0;
//		vy = 0;
//		ay = 0;
//		break;
//	case GOOMBA_STATE_WALKING:
//		vx = -GOOMBA_WALKING_SPEED;
//		break;
//	}
//}