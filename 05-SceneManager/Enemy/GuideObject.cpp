#include "GuideObject.h"
#include "Koopa.h" 

void CGuideObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float kvx, kvy;
	koopa->GetSpeed(kvx, kvy);
	this->SetSpeed(kvx, kvy);
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}

