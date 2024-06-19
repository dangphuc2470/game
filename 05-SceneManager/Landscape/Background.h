#pragma once

#include "../GameObject/GameObject.h"
#include "../Game/Animation.h"
#include "../Game/Animations.h"
#include "../GameObject/AssetIDs.h"


class CLargeBush1 : public CGameObject {
public:
	CLargeBush1(float x, float y) : CGameObject(x, y) {}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_LARGE_BUSH_1)->Draw(x, y);
	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
};


class CLargeBush2 : public CGameObject {
public:
	CLargeBush2(float x, float y) : CGameObject(x, y) {}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_LARGE_BUSH_2)->Draw(x, y);
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


class CSmallBush : public CGameObject {
public:
	int length;

	CSmallBush(float x, float y, int length) : CGameObject(x, y) {
		this->length = length;
	}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		for (int i = 0; i < this->length; i++) {
			s->Get(ID_SPRITE_SMALL_BUSH)->Draw(x + i * 16, y);
		}
		//s->Get(ID_SPRITE_SMALL_BUSH)->Draw(x, y);
	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
};

class CBlackBackground : public CGameObject {
	
public:
	CBlackBackground(float x, float y) : CGameObject(x, y) {}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_BLACK_BACKGROUND)->Draw(x, y);
	};
	int cellWidth = 335;
	int cellHeight = 415;

	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = x - (this->cellWidth / 2);
		t = y - (this->cellHeight / 2);
		r = l + this->cellWidth; 
		b = t + this->cellHeight;
	};
	int IsBlocking() { return 0; }

	int GetSceneId() {
		return 2; // Todo: change this to the correct scene id
	};
};

