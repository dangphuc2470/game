#include "GameObject.h"
#include "Koopa.h"

CKoopa::CKoopa(float x, float y, float vx) :CGameObject(x, y)
{
	this->vx = vx;
};

void CKoopa::Update(DWORD dt)
{
	x += vx * dt;

	int BackBufferWidth = CGame::GetInstance()->GetBackBufferWidth();
	if (x <= 0 || x >= BackBufferWidth - KOOPA_WIDTH) {

		vx = -vx;

		if (x <= 0)
		{
			x = 0;
		}
		else if (x >= BackBufferWidth - KOOPA_WIDTH)
		{
			x = (float)(BackBufferWidth - KOOPA_WIDTH);
		}
	}
}

void CKoopa::Render()
{
	LPANIMATION ani;

	//[RED FLAG][TODO]: Student needs to think about how to associate this animation/asset to Mario!!
	if (vx > 0) ani = CAnimations::GetInstance()->Get(540);
	else ani = CAnimations::GetInstance()->Get(530);

	ani->Render(x, y);
}
