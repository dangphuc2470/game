#pragma once
#include "../Game/Game.h"
#include "../Game/Textures.h"
#include "Scene.h"
#include "../GameObject/GameObject.h"
#include "../Landscape/Brick.h"
#include "../Mario.h"
#include <string>



class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					

	vector<LPGAMEOBJECT> objects;

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

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	vector<LPGAMEOBJECT> GetObjects() { return objects; }
	void AddObject(LPGAMEOBJECT obj) {
		objects.push_back(obj);
	}

	void TurnBrickIntoCoin();
};

typedef CPlayScene* LPPLAYSCENE;

