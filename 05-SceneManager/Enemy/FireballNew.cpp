#include "NewFireball.h"
#include "../Scene/PlayScene.h"
#include "Koopa.h"
#include "Ptooie.h"

void CFireballnew::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (dynamic_cast<CGuideObject*> (e->obj))
	{
		CGuideObject* guide = dynamic_cast<CGuideObject*>(e->obj);
		guide->DeleteKoopa();
		isDeleted = true;

	}

	if (dynamic_cast<CKoopa*> (e->obj))
	{
		CKoopa* koopa = dynamic_cast<CKoopa*>(e->obj);
		if (koopa->GetState() != KOOPA_STATE_DIE)
			koopa->SetState(KOOPA_STATE_DIE);
		else
			koopa->SetCollidable(false);
		isDeleted = true;

	}
	if (dynamic_cast<CGoomba*> (e->obj))
	{
		CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
		goomba->SetCollidable(false);
		isDeleted = true;

	}
	if (dynamic_cast<CMysteryBox*> (e->obj))
	{
		CMysteryBox* box = dynamic_cast<CMysteryBox*>(e->obj);
		box->SetState(MBOX_STATE_UNBOX);
		isDeleted = true;

	}
	if (dynamic_cast<CBrick*> (e->obj))
	{
		CBrick* brick = dynamic_cast<CBrick*>(e->obj);
		brick->SetState(BRICK_STATE_BROKEN);
		isDeleted = true;

	}
	if (dynamic_cast<CPtooie*> (e->obj))
	{
		CPtooie* ptooie = dynamic_cast<CPtooie*>(e->obj);
		ptooie->SetState(PTOOIE_STATE_DIE);
		isDeleted = true;
	}
	if (dynamic_cast<CMushroom*> (e->obj))
	{
		CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
		mushroom->SetState(MUSHROOM_STATE_MOVING_UP);
		isDeleted = true;
	}
	if (dynamic_cast<CLeaf*> (e->obj))
	{
		CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
		leaf->SetState(LEAF_STATE_MOVING_UP);
		isDeleted = true;
	}



	if (dynamic_cast<CFireballnew*>(e->obj)) return;
	if (dynamic_cast<CMario*> (e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
		isDeleted = true;
	}
	else if (e->nx != 0)
	{
		vx = 0;
		isDeleted = true;

	}
}