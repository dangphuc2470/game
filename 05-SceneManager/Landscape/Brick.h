#pragma once

#include "../GameObject/GameObject.h"
#include "../Game/Animation.h"
#include "../Game/Animations.h"
#include "../Mario.h"
#include "../GameObject/AssetIDs.h"
#include <stdio.h>
#include <map>

#define BRICK_BBOX_WIDTH 15
#define BRICK_BBOX_HEIGHT 15
#define BRICK_STATE_NORMAL 100
#define BRICK_STATE_BROKEN 200
#define BRICK_BROKEN_TIMEOUT 760 
#define BRICK_BROKEN_SPRITE_START 20005 
#define BRICK_BROKEN_SPRITE_END 20016

class CBrick : public CGameObject {
public:
	ULONGLONG broken_start;
	int currentSpriteId;
	map<int, int> spriteTimes;

	CBrick(float x, float y) : CGameObject(x, y) {
		broken_start = -1;
		currentSpriteId = BRICK_BROKEN_SPRITE_START;
		spriteTimes = {
			{BRICK_BROKEN_SPRITE_START + 1, 40},
			{BRICK_BROKEN_SPRITE_START + 2, 40},
			{BRICK_BROKEN_SPRITE_START + 3, 40},
			{BRICK_BROKEN_SPRITE_START + 4, 40},
			{BRICK_BROKEN_SPRITE_START + 5, 40},
			{BRICK_BROKEN_SPRITE_START + 6, 40},
			{BRICK_BROKEN_SPRITE_START + 7, 120},
			{BRICK_BROKEN_SPRITE_START + 8, 80},
			{BRICK_BROKEN_SPRITE_START + 9, 80},
			{BRICK_BROKEN_SPRITE_START + 10, 80},
			{BRICK_BROKEN_SPRITE_START + 11, 80},
			{BRICK_BROKEN_SPRITE_START + 12, 80}
		};
	}
	void Render()
	{
		//DebugOutTitle(L"Brick state: %d\n", state);
		if (state == BRICK_STATE_BROKEN)
		{
			CSprites* sprites = CSprites::GetInstance();
			sprites->Get(currentSpriteId)->Draw(x, y);
			// Can't use animation because it have some bugs that make the second broken brick 
			// not render from start sprite, but from end
		}
		else
		{
			CAnimations* animations = CAnimations::GetInstance();
			animations->Get(ID_ANI_BRICK)->Render(x, y);
		}
		//RenderBoundingBox();
	};

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		if (state == BRICK_STATE_BROKEN)
		{
			if (GetTickCount64() - broken_start > spriteTimes[currentSpriteId])
			{
				broken_start = GetTickCount64();
				currentSpriteId++;
				if (currentSpriteId > BRICK_BROKEN_SPRITE_END)
				{
					isDeleted = true;
				}
			}
		}
		CGameObject::Update(dt);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	};

	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - BRICK_BBOX_WIDTH / 2;
		t = y - BRICK_BBOX_HEIGHT / 2;
		r = l + BRICK_BBOX_WIDTH;
		b = t + BRICK_BBOX_HEIGHT;
	};

	void SetState(int state) {
		CGameObject::SetState(state);
		if (state == BRICK_STATE_BROKEN && broken_start == -1)
		{
			broken_start = GetTickCount64();
			SetBlocking(false);
		}
	}

};