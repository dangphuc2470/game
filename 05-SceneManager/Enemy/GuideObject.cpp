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

void CGuideObject::DeleteKoopa()
{
	if (koopa->GetState() != KOOPA_STATE_DIE)
		koopa->SetState(KOOPA_STATE_DIE);
	else
		koopa->SetCollidable(false);
	/*koopa->SetCollidable(false);
	isDeleted = true;*/
}
//
//void CGuideObjectMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
//    ULONGLONG currentTime = GetTickCount64();
//    int changeTime = 4000;
//    int timeMod = currentTime % changeTime;
//    float vx;
//    if (timeMod < changeTime/4) {
//        vx = -1.0f; // Move left in the first third
//    }
//    else if (timeMod < (changeTime/4) * 2) {
//        vx = 0.0f; // Stop in the middle third
//        float marioX, marioY;
//        mario->GetPosition(marioX, marioY);
//        SetPosition(marioX, marioY);
//    }
//    else if (timeMod < (changeTime / 4) * 3){
//        vx = 1.0f; // Move right in the last third
//    }
//	else {
//		vx = 0.0f; // Stop in the last third
//        float marioX, marioY;
//        mario->GetPosition(marioX, marioY);
//        SetPosition(marioX, marioY);
//	}
//
//    x += vx * dt;
//
//    DebugOutTitle(L"Vx: %f", vx);
//    CGameObject::Update(dt, coObjects);
//    CCollision::GetInstance()->Process(this, dt, coObjects);
//}
//
