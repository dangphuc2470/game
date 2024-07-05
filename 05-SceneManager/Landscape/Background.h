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

class CFlower : public CGameObject {
	public:
	CFlower(float x, float y) : CGameObject(x, y) {}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_FLOWER)->Draw(x, y);
	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
};

class CCloudSolid : public CGameObject {
	float size = 15;
	public:
	CCloudSolid(float x, float y) : CGameObject(x, y) {
	}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_CLOUD_SOLID)->Draw(x, y);
		//RenderBoundingBox();
	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = x - size / 2;
		t = y - size / 2;
		r = l + size;
		b = t + size;
	};
	int IsDirectionColliable(float nx, float ny)
	{
		if (nx == 0 && ny == -1) return 1;
		else return 0;
	}
};

class CBunker : public CGameObject
{
public:
	CBunker(float x, float y) : CGameObject(x, y) {}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_BUNKER)->Draw(x, y);

	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
};

class CMap : public CGameObject
{
	ULONGLONG map_loading_start = -1;
	int currentScene = 0;
	CGameObject* mario;
public:
	std::vector<float> mapX;
	std::vector<float> mapY;

	CMap(float x, float y) : CGameObject(x, y) {
		SetMapScenePosition();
	}

	void SetMapScenePosition()
	{
		mapX = { 74, 123, 166, 210, 249, 296 };
		mapY = { 16, 60, 104, 148, 192 };
	}

	void Render()
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_MAP)->Render(x, y);

		if (map_loading_start != -1)
		{
			mario->SetPosition(-100, -100); // Hide mario when loading map
			CBlackBackground *blackBackground = new CBlackBackground(x + 74, y + 16);
			CBlackBackground *blackBackground2 = new CBlackBackground(x - 50, y + 16);
			blackBackground->Render();
			blackBackground2->Render();
		}
	};
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		if (map_loading_start != -1 && GetTickCount64() - map_loading_start > 500)
		{
			SwitchToScene(currentScene);
		}

		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }

	void SwitchToScene(int sceneID)
	{
		CGame::GetInstance()->InitiateSwitchScene(sceneID);
	}

	void MoveToMap(int currentIndexX, int currentIndexY, CGameObject* mario)
	{
		this->mario = mario;
		if (currentIndexX == 1 && currentIndexY == 0)
		{
			currentScene = 1; //Scene 1
			map_loading_start = GetTickCount64();
		}
		else if (currentIndexX == 3 && currentIndexY == 0)
		{
			currentScene = 1; //Scene 2
			map_loading_start = GetTickCount64();
		}
		else if (currentIndexX == 4 && currentIndexY == 0)
		{
			currentScene = 1; //Scene 3
			map_loading_start = GetTickCount64();
		}

		else if (currentIndexX == 5 && currentIndexY == 1)
		{
			currentScene = 1; //Scene Mushroom
			map_loading_start = GetTickCount64();
		}
		else if (currentIndexX == 4 && currentIndexY == 1)
		{
			currentScene = 1; //Scene 4
			map_loading_start = GetTickCount64();
		}

		else if (currentIndexX == 3 && currentIndexY == 2)
		{
			currentScene = 1; //Scene Spades
			map_loading_start = GetTickCount64();
		}

		else if (currentIndexX == 2 && currentIndexY == 2)
		{
			currentScene = 1; //Scene Tower
			map_loading_start = GetTickCount64();
		}

		else if (currentIndexX == 1 && currentIndexY == 4)
		{
			currentScene = 1; //Scene 5
			map_loading_start = GetTickCount64();
		}
		else if (currentIndexX == 3 && currentIndexY == 4)
		{
			currentScene = 1; //Scene 6
			map_loading_start = GetTickCount64();
		}

		else if (currentIndexX == 2 && currentIndexY == 3)
		{
			currentScene = 1; //Scene Mushroom 2
			map_loading_start = GetTickCount64();
		}

		else if (currentIndexX == 5 && currentIndexY == 3)
		{
			currentScene = 1; //Scene End
			map_loading_start = GetTickCount64();
		}


			
	}
};

class CIntro : public CGameObject
{
public:
	CIntro(float x, float y) : CGameObject(x, y) {}
	void Render()
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_INTRO)->Render(x, y);
	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
};

class CBlackEnd : public CGameObject
{
public:
	CBlackEnd(float x, float y) : CGameObject(x, y) {}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_BLACK_END)->Draw(x, y);
	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	int IsBlocking() { return 0; }
};