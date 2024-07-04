#pragma once
#include "../Game/Game.h"
#include "../Game/Textures.h"
#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "../Landscape/Brick.h"
#include "../Mario.h"
#include <string>
#define CAM_SHAKE_DURATION 500



class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;
	LPGAMEOBJECT marioMap = NULL;
	LPGAMEOBJECT infoBar;
	int live = 4;
	int point = 0;
	int coin = 0;
	vector<LPGAMEOBJECT> objects;
	bool isCameraShake = false;
	ULONGLONG cameraShakeStart = -1;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);
	float cam_y = 0;
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }
	LPGAMEOBJECT GetMarioMap() { return marioMap; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	vector<LPGAMEOBJECT> GetObjects() { return objects; }
	void AddObject(LPGAMEOBJECT obj) {
		objects.push_back(obj);
	}

	void TurnBrickIntoCoin();
	void ShakeCamera();

	int GetLive()
	{
		return live;
	}

	int GetPoint()
	{
		return point;
	}

	int GetCoin()
	{
		return coin;
	}

	void SetLive(int live)
	{
		this->live = live;
	}

	void SetCoin(int coin)

	{
		this->coin = coin;
	}

	void SetPoint(int point)
	{
		this->point = point;
	}
};

typedef CPlayScene* LPPLAYSCENE;

