#pragma once

#include "../GameObject/GameObject.h"
#include "../Game/Animation.h"
#include "../Game/Animations.h"
#include "../GameObject/AssetIDs.h"

class CPoint : public CGameObject {
public:
	int point = 100;
	ULONGLONG timeAppear = -1;
	CPoint(float x, float y, int point) : CGameObject(x, y) {
		this->point = point;
		timeAppear = GetTickCount64();
	}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_POINT_100)->Draw(x, y);
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if(GetTickCount64() - timeAppear > 1000)
		{
			isDeleted = true;
		}
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
};