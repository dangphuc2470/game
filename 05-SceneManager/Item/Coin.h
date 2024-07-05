#pragma once

#include "../GameObject/GameObject.h"
#include "../Game/Animation.h"
#include "../Game/Animations.h"
#include "../Scene/PlayScene.h"
#include "Point.h"
class CPlayScene;

#define ID_ANI_COIN 11000

#define	COIN_WIDTH 10
#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

class CCoin : public CGameObject {
public:
	CCoin(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};


class CCoinSplash : public CGameObject {
public:
	float targetY;
	bool isFalling = false;
	CCoinSplash(float x, float y) : CGameObject(x, y) 
	{
		this->targetY = y - 30;
		SetBlocking(0);
		SetCollidable(0);
	}

	void Render()
	{
		CAnimations::GetInstance()->Get(ID_ANI_COIN)->Render(x, y);
	}

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);

	void GetBoundingBox(float& l, float& t, float& r, float& b) {};

	int IsBlocking() { return 0; }
	~CCoinSplash() {};
};