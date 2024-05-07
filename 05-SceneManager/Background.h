#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"

#define COIN_BBOX_WIDTH 10
#define COIN_BBOX_HEIGHT 16

class CLargeBrush1 : public CGameObject {
public:
	CLargeBrush1(float x, float y) : CGameObject(x, y) {}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_LARGE_BRUSH_1)->Draw(x, y);
	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
};

class CLargeBrush2 : public CGameObject {
public:
	CLargeBrush2(float x, float y) : CGameObject(x, y) {}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_LARGE_BRUSH_2)->Draw(x, y);
	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
};

class CCloud1 : public CGameObject {
public:
	CCloud1(float x, float y) : CGameObject(x, y) {}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_CLOUD_1)->Draw(x, y);
	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
};

class CCloud2 : public CGameObject {
public:
	CCloud2(float x, float y) : CGameObject(x, y) {}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_CLOUD_2)->Draw(x, y);
	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
};