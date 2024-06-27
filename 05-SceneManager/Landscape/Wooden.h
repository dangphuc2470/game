#pragma once

#include "../GameObject/GameObject.h"
#include "../Game/Animation.h"
#include "../Game/Animations.h"
#include "../Mario.h"
#include "../GameObject/AssetIDs.h"

#define WOODEN_BBOX_WIDTH 15
#define WOODEN_BBOX_HEIGHT 15

class CWooden : public CGameObject {
public:
	CWooden(float x, float y) : CGameObject(x, y) {};
	
	void Render()
	{
		CSprites* sprites = CSprites::GetInstance();
		sprites->Get(ID_SPRITE_WOODEN)->Draw(x, y);
		//RenderBoundingBox();
	};

	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - WOODEN_BBOX_WIDTH / 2;
		t = y - WOODEN_BBOX_HEIGHT / 2;
		r = l + WOODEN_BBOX_WIDTH;
		b = t + WOODEN_BBOX_HEIGHT;
	};

};

