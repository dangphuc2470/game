#pragma once

#include "../GameObject/GameObject.h"
#include "../Game/Animation.h"
#include "../Game/Animations.h"
#include "../Mario.h"
#include "../GameObject/AssetIDs.h"

#define BUTTON_BBOX_WIDTH 13
#define BUTTON_BBOX_HEIGHT 11
#define BUTTON_STATE_NORMAL 100
#define BUTTON_STATE_PRESSED 200

class CButton : public CGameObject {
	float targetY;
	bool isMovingUp = false;
public:
	CButton(float x, float y) : CGameObject(x, y) {
	SetState(BUTTON_STATE_NORMAL);
	SetBlocking(false);
	SetCollidable(true);
	targetY = y - 15;
	};

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
	{
		if (isMovingUp)
		{
			if (y > targetY)
				y -= 0.1f * dt;
			else
			{
				isMovingUp = false;
			}
		}
		CGameObject::Update(dt);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	};

	void Render()
	{
		CSprites* sprites = CSprites::GetInstance();
		if (state == BUTTON_STATE_PRESSED)
			sprites->Get(ID_SPRITE_BUTTON_PRESSED)->Draw(x, y);
		else
		{
			CAnimations* animations = CAnimations::GetInstance();
			animations->Get(ID_ANI_BUTTON_NORMAL)->Render(x, y);
		}
		//RenderBoundingBox();
	};

	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - BUTTON_BBOX_WIDTH / 2;
		t = y - BUTTON_BBOX_HEIGHT / 2;
		r = l + BUTTON_BBOX_WIDTH;
		b = t + BUTTON_BBOX_HEIGHT;
	};

	void SetState(int state) { 
		CGameObject::SetState(state);
	};

	void MoveUp()
	{
		isMovingUp = true;
	}

};

