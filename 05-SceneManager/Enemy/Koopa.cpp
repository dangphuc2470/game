#include "Koopa.h"
#include "../Landscape/MysteryBox.h"
// #include "Koopa.h"

// CKoopa::CKoopa(float x, float y):CGameObject(x, y)
// {
// 	this->ax = 0;
// 	this->ay = KOOPA_GRAVITY;
// 	die_start = -1;
// 	SetState(KOOPA_STATE_WALKING);
// }

// void CKoopa::GetBoundingBox(float &left, float &top, float &right, float &bottom)
// {
// 	if (state == KOOPA_STATE_DIE)
// 	{
// 		left = x - KOOPA_BBOX_WIDTH/2;
// 		top = y - KOOPA_BBOX_HEIGHT_DIE/2;
// 		right = left + KOOPA_BBOX_WIDTH;
// 		bottom = top + KOOPA_BBOX_HEIGHT_DIE;
// 	}
// 	else
// 	{ 
// 		left = x - KOOPA_BBOX_WIDTH/2;
// 		top = y - KOOPA_BBOX_HEIGHT/2;
// 		right = left + KOOPA_BBOX_WIDTH;
// 		bottom = top + KOOPA_BBOX_HEIGHT;
// 	}
// }

// void CKoopa::OnNoCollision(DWORD dt)
// {
// 	x += vx * dt;
// 	y += vy * dt;
// };

// void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
// {
// 	if (!e->obj->IsBlocking()) return; 
// 	if (dynamic_cast<CKoopa*>(e->obj)) return; 

// 	if (e->ny != 0 )
// 	{
// 		vy = 0;
// 	}
// 	else if (e->nx != 0)
// 	{
// 		vx = -vx;
// 	}
// }

// void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
// {
// 	vy += ay * dt;
// 	vx += ax * dt;

// 	if ( (state==KOOPA_STATE_DIE) && (GetTickCount64() - die_start > KOOPA_DIE_TIMEOUT) )
// 	{
// 		isDeleted = true;
// 		return;
// 	}

// 	CGameObject::Update(dt, coObjects);
// 	CCollision::GetInstance()->Process(this, dt, coObjects);
// }


// void CKoopa::Render()
// {
// 	int aniId = ID_ANI_KOOPA_WALKING;
// 	if (state == KOOPA_STATE_DIE) 
// 	{
// 		aniId = ID_ANI_KOOPA_DIE;
// 	}

// 	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
// 	RenderBoundingBox();
// }

// void CKoopa::SetState(int state)
// {
// 	CGameObject::SetState(state);
// 	switch (state)
// 	{
// 		case KOOPA_STATE_DIE:
// 			die_start = GetTickCount64();
// 			y += (KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE)/2;
// 			vx = 0;
// 			vy = 0;
// 			ay = 0; 
// 			break;
// 		case KOOPA_STATE_WALKING: 
// 			vx = -KOOPA_WALKING_SPEED;
// 			break;
// 	}
// }

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
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
				if (this->mario!= NULL)
				{
					this->mario->AddPoint(100);
				}
				//koopa->isDeleted = true;
			}
			return;
		}
		else if (dynamic_cast<CMysteryBox*>(e->obj))
		{
			CMysteryBox* box = dynamic_cast<CMysteryBox*>(e->obj);
			box->SetState(MBOX_STATE_UNBOX);
			this->x = this->x - KOOPA_REFLECT;
			this->y = this->y - KOOPA_REFLECT;

		}
		else if (dynamic_cast<CGoomba*>(e->obj) && (this->state == KOOPA_STATE_DIE_SLIP))
		{
			CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
			//goomba->SetState(GOOMBA_STATE_DIE);
			if (this->mario != NULL)
			{
				this->mario->AddPoint(100);
			}
			goomba->SetCollidable(false);
		}
		else if (dynamic_cast<CBrick*>(e->obj) && (this->state == KOOPA_STATE_DIE_SLIP))
		{
			CBrick* brick = dynamic_cast<CBrick*>(e->obj);
			if (nx != 0)
			{
				vx = -vx;
				brick->SetState(BRICK_STATE_BROKEN);
			}
		}
		else if (dynamic_cast<CMushroom*>(e->obj) && (this->state == KOOPA_STATE_DIE_SLIP))
		{
			CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
			if (mushroom->GetState() == MUSHROOM_STATE_IDLE)
			mushroom->SetState(MUSHROOM_STATE_MOVING_UP);
		}
		else if (dynamic_cast<CLeaf*>(e->obj) && (this->state == KOOPA_STATE_DIE_SLIP))
		{
			CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
			if (marioToGetPos->GetLevel() == MARIO_LEVEL_SMALL)
			{
				leaf->ChangeToMushroom();
			}
			else
			{
				leaf->SetState(LEAF_STATE_MOVING_UP);
			}
		}

		if (!e->obj->IsBlocking()) return;
		if (e->ny != 0)
		{
			vy = 0;
		}
		else if (e->nx != 0)
			ChangeDirection();
	
}
