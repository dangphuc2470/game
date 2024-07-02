#include "Leaf.h"
#include "../Enemy/Koopa.h"

void CLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMario*>(e->obj)) return;
	if (dynamic_cast<CLeaf*>(e->obj)) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CKoopa*>(e->obj))
	{
		isDeleted = true;
	}
	if (dynamic_cast<CFireBall*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}

}

void CLeaf::ChangeToMushroom()
{
	CMushroom* mushroom = new CMushroom(x, y);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	mushroom->SetPosition(x, y);
	mushroom->SetState(MUSHROOM_STATE_MOVING_UP);
	scene->AddObject(mushroom);
	isDeleted = true;
}