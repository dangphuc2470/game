
#pragma once
#include "../GameObject/GameObject.h"
#include "../Game/Animation.h"
#include "../Game/Animations.h"
#include "../Mario.h"
#include "../GameObject/AssetIDs.h"
#include <stdio.h>
#include <map>

#define MBOX_BBOX_WIDTH 15
#define MBOX_BBOX_HEIGHT 15
#define MBOX_STATE_NORMAL 100
#define MBOX_STATE_UNBOX 200

class CMysteryBox : public CGameObject {
public:
	CMysteryBox(float x, float y) : CGameObject(x, y) {}
	void Render()
	{
		//DebugOutTitle(L"MBOX state: %d\n", state);
		if (state == MBOX_STATE_UNBOX)
		{
			CSprites* sprites = CSprites::GetInstance();
			sprites->Get(ID_SPRITE_MYSTERY_BOX_UNBOX)->Draw(x, y);
		}
		else
		{
			CAnimations* animations = CAnimations::GetInstance();
			animations->Get(ID_ANI_MYSTERY_BOX)->Render(x, y);
		}
		RenderBoundingBox();
	};

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		
		CGameObject::Update(dt);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	};

	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - MBOX_BBOX_WIDTH / 2;
		t = y - MBOX_BBOX_HEIGHT / 2;
		r = l + MBOX_BBOX_WIDTH;
		b = t + MBOX_BBOX_HEIGHT;
	};

	void SetState(int state) {
		CGameObject::SetState(state);
	}

};