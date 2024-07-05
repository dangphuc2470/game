#include "Coin.h"

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoinSplash::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	if (y > targetY && !isFalling)
	{
		y -= 0.1f * dt;
		if (y < targetY)
			y = targetY;
	}

	if (y == targetY)
		isFalling = true;

	if (isFalling)
	{
		if (y > targetY - 30)
		{
			isDeleted = true;

			CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
			CPoint* point = new CPoint(x, y, 100);
			scene->AddObject(point);
		}
		else
			y += 0.1f * dt;
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}