#pragma once

#include "../GameObject/GameObject.h"
#include "../Game/Animation.h"
#include "../Game/Animations.h"
#include "../Mario.h"
#include "../GameObject/AssetIDs.h"

#define BRICK_BBOX_WIDTH 15
#define BRICK_BBOX_HEIGHT 15
#define BRICK_STATE_NORMAL 100
#define BRICK_STATE_BROKEN 200
#define BRICK_BROKEN_TIMEOUT 500

class CBrick : public CGameObject {
public:
	ULONGLONG broken_start;
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render()
	{
		//DebugOutTitle(L"Brick state: %d\n", state);
		/*if (state == BRICK_STATE_BROKEN)
			return;*/
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_BRICK)->Render(x, y);
		//RenderBoundingBox();
	};
	void Update(DWORD dt) {
		DebugOutTitle(L"Tick Count: %d\n", GetTickCount64() - broken_start);
		if (state == BRICK_STATE_BROKEN && GetTickCount64() - broken_start > BRICK_BROKEN_TIMEOUT)
			isDeleted = true;
		CGameObject::Update(dt);

	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - BRICK_BBOX_WIDTH/2;
		t = y - BRICK_BBOX_HEIGHT/2;
		r = l + BRICK_BBOX_WIDTH;
		b = t + BRICK_BBOX_HEIGHT;
	};

	void SetState(int state) { 
		CGameObject::SetState(state);
		if (state == BRICK_STATE_BROKEN)
			broken_start = GetTickCount64();

	}

};