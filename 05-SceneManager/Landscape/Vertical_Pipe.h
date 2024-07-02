#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
#include "../Mario.h"
#define PIPE_BBOX_WIDTH  31
#define PIPE_BBOX_HEIGHT 192

class CVerticalPipe : public CGameObject
{
	bool isGetDownAble;
	ULONGLONG block_start = -1;
public:
	CVerticalPipe(float x, float y, bool isGetDownAble = false) : CGameObject(x, y) {
		this->isGetDownAble = isGetDownAble;
		SetCollidable(true);
	}
	void Render()
	{
		CSprites* sprites = CSprites::GetInstance();
		sprites->Get(ID_SPRITE_VERTICAL_PIPE)->Draw(x, y);
		//RenderBoundingBox();

	};


	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if (block_start != -1 && GetTickCount64() - block_start > 1000)
		{
			SetBlocking(true);
			block_start = -1;
		}
		//CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - PIPE_BBOX_WIDTH / 2;
		t = y - PIPE_BBOX_HEIGHT / 2;
		r = l + PIPE_BBOX_WIDTH;
		b = t + PIPE_BBOX_HEIGHT;
	};

	bool GetIsGetDownAble() { return isGetDownAble; }

	void BlockFor1s()
	{
		block_start = GetTickCount64();
		SetBlocking(false);
	}
};

