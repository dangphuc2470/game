﻿#include <iostream>
#include <fstream>
#include "../GameObject/AssetIDs.h"

#include "PlayScene.h"
#include "../Game/Utils.h"
#include "../Game/Textures.h"
#include "../Game/Sprites.h"
#include "../Item/Coin.h"
#include "../Item/Button.h"
#include "../Landscape/Portal.h"
#include "../Landscape/Platform.h"
#include "../Landscape/BrickPlatform.h"
#include "../Landscape/Background.h"
#include "../Landscape/Box.h"
#include "../Landscape/Vertical_Pipe.h"
#include "../Landscape/MysteryBox.h"
#include "../Landscape/Spawner.h"
#include "../Landscape/Teleport.h"
#include "../Enemy/Koopa.h"
#include "../Enemy/Goomba.h"
#include "../Enemy/Ptooie.h"
#include "../Landscape/Wooden.h"
#include "InfoBar.h"

#include "../Game/SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	DebugOutTitle(L"Super Mario Bros 3");
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (size_t i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		if (tokens.size() > 4)
		{
			int isNoCountDown = atoi(tokens[3].c_str());
			CGame* game = CGame::GetInstance();
			int* coinPtr = game->GetCoinPtr(); 
			int* pointPtr = game->GetPointPtr(); 
			int* livePtr = game->GetLivePtr(); 
			obj = new CMario(x, y, coinPtr, pointPtr, livePtr, isNoCountDown);
		}
		else
		{
			CGame* game = CGame::GetInstance();
			int* coinPtr = game->GetCoinPtr(); 
			int* pointPtr = game->GetPointPtr(); 
			int* livePtr = game->GetLivePtr(); 
			obj = new CMario(x, y, coinPtr, pointPtr, livePtr, false);
		}
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y); break;
	case OBJECT_TYPE_GOOMBA_WINGS: obj = new CGoomba(x, y, true); break;
	case OBJECT_TYPE_KOOPA_RED: obj = new CKoopa(x, y, false, false, player); break;
	case OBJECT_TYPE_KOOPA_RED_WINGS: obj = new CKoopa(x, y, false, true, player); break;
	case OBJECT_TYPE_KOOPA_GREEN: obj = new CKoopa(x, y, true, false, player); break;
	case OBJECT_TYPE_KOOPA_GREEN_WINGS: obj = new CKoopa(x, y, true, true, player); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
	case OBJECT_TYPE_LARGE_BUSH_1: obj = new CLargeBush1(x, y); break;
	case OBJECT_TYPE_LARGE_BUSH_2: obj = new CLargeBush2(x, y); break;
	case OBJECT_TYPE_CLOUD_1: obj = new CCloud1(x, y); break;
	case OBJECT_TYPE_CLOUD_2: obj = new CCloud2(x, y); break;
	case OBJECT_TYPE_BLACK_BACKGROUND: obj = new CBlackBackground(x, y); break;
	case OBJECT_TYPE_BLACK_END: obj = new CBlackEnd(x, y); break;
	case OBJECT_TYPE_BUTTON: obj = new CButton(x, y); break;
	case OBJECT_TYPE_FLOWER: obj = new CFlower(x, y); break;
	case OBJECT_TYPE_CLOUD_SOLID: obj = new CCloudSolid(x, y); break;
	case OBJECT_TYPE_BUNKER: obj = new CBunker(x, y); break;
	case OBJECT_TYPE_INTRO: obj = new CIntro(x, y); break;
	case OBJECT_TYPE_RANDOM_BLACK_END: obj = new CRandom(x, y); break;
	case OBJECT_TYPE_MAP: 
	{
		obj = new CMap(x, y); 
		this->map = obj;
		break;
	}
	case OBJECT_TYPE_MARIO_MAP: 
	{
		obj = new CMarioMap(x, y, map);
		this->marioMap = obj;
		break;
	}
	case OBJECT_TYPE_INFO_BAR:
	{
		obj = new CInfoBar(x, y, player, this);
		this->infoBar = obj;
		break;
	}
	case OBJECT_TYPE_LETTER_NUMBER_BAR:
	{
		int letter = atoi(tokens[3].c_str());
		obj = new CLetter(x, y, letter);
		break;
	}
	case OBJECT_TYPE_VERTICAL_PIPE:
	{
		if (tokens.size() > 3)
		{
			bool isGetdownAble = atoi(tokens[3].c_str());
			obj = new CVerticalPipe(x, y, isGetdownAble);
		}
		else
			obj = new CVerticalPipe(x, y); break;
	}
	case OBJECT_TYPE_TELEPORT:
	{
		float targetX = static_cast<float>(atof(tokens[3].c_str()));
		float targetY = static_cast<float>(atof(tokens[4].c_str()));
		obj = new CTeleport(x, y, targetX, targetY);
		break;
	}
	case OBJECT_TYPE_PTOOIE:
	{
		int isRed = atoi(tokens[3].c_str());
		int isBite = atoi(tokens[4].c_str());
		obj = new CPtooie(x, y, player, isRed, isBite); break;
	}
	case OBJECT_TYPE_SPAWNER:
	{
		int type = atoi(tokens[3].c_str());
		float objY = static_cast<float>(atoi(tokens[5].c_str()));
		float objX = static_cast<float>(atoi(tokens[4].c_str()));
		obj = new CSpawner(x, y, type, objX, objY);
		break;
	}
	case OBJECT_TYPE_MYSTERY_BOX:
	{
		bool isOpened = atoi(tokens[3].c_str());
		int objectToSpawn = -1;
		if (tokens.size() > 4)
		{
			objectToSpawn = atoi(tokens[4].c_str());
		}

		if (tokens.size() > 5)
		{
			bool isBrick = atoi(tokens[5].c_str());
			obj = new CMysteryBox(x, y, isOpened, objectToSpawn, isBrick);
		}
		else
			obj = new CMysteryBox(x, y, isOpened, objectToSpawn); break;
	}
	case OBJECT_TYPE_BOX_PLATFORM:
	{
		float width = static_cast<float>(atoi(tokens[3].c_str()));
		float height = static_cast<float>(atoi(tokens[4].c_str()));
		int box_type_sprite_id = atoi(tokens[5].c_str());
		obj = new CBoxPlatform(x, y, width, height, box_type_sprite_id);
		break;
	}
	case OBJECT_TYPE_SMALL_BUSH:
	{
		int length = atoi(tokens[3].c_str());
		obj = new CSmallBush(x, y, length);
		break;

	}
	case OBJECT_TYPE_WOODEN: obj = new CWooden(x, y); break;

	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_BRICK_PLATFORM:
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CBrickPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);


		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{

	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 


	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);


	CGame* game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;

	if (cx < 0) cx = 0;

	CMario* mario = dynamic_cast<CMario*>(player);

	float finalCamX, finalCamY = 0;


	int level = mario->GetLevel();
	if (mario->GetIsFlying() || (cy < -120 && cx > 500))
	{
		float x, y;
		mario->GetPosition(x, y);
		if (y > 30)
		{
			float targetCamY = cy;
			float camMoveSpeedY = static_cast<float>(0.05 * dt);

			// Cập nhật vị trí camera Y dần dần về mục tiêu
			if (cam_y < targetCamY)
			{
				cam_y += camMoveSpeedY * dt;
				if (cam_y > targetCamY) // Tránh vượt quá mục tiêu
				{
					cam_y = targetCamY;
				}
			}
			else if (cam_y > targetCamY)
			{
				cam_y -= camMoveSpeedY * dt;
				if (cam_y < targetCamY) // Tránh vượt quá mục tiêu
				{
					cam_y = targetCamY;
				}
			}
			if (cam_y > 0)
				cam_y = 0;

			finalCamX = cx;
			finalCamY = cam_y;
		}
		else {
			finalCamX = cx;
			finalCamY = cy;
		}
	}
	else
	{
		float targetCamY = 0.0f;
		float camMoveSpeedY = static_cast<float>(0.05 * dt);

		if (cam_y < targetCamY)
		{
			cam_y += camMoveSpeedY * dt;
			if (cam_y > targetCamY)
			{
				cam_y = targetCamY;
			}
		}
		else if (cam_y > targetCamY)
		{
			cam_y -= camMoveSpeedY * dt;
			if (cam_y < targetCamY)
			{
				cam_y = targetCamY;
			}
		}

		// Cập nhật vị trí camera
		finalCamX = cx;
		finalCamY = cam_y;
	}


	if (isCameraShake)
	{
		ULONGLONG now = GetTickCount64();
		if (now - cameraShakeStart > CAM_SHAKE_DURATION)
		{
			isCameraShake = false;
		}
		else
		{
			finalCamX += rand() % 5 - 2;
			finalCamY += rand() % 5 - 2;
		}
	}

	if (finalCamY < -275)
		finalCamY = -275;

	if (finalCamX > 2610 && finalCamX < 3000) // End screen, > 3000 use for black underground
		finalCamX = 2610;
	//DebugOutTitle(L"CamX: %f, CamY: %f", finalCamX, finalCamY);
	CGame::GetInstance()->SetCamPos(finalCamX, finalCamY);
	if (infoBar != NULL)
		infoBar->SetPosition(finalCamX + 240, finalCamY + 240);
	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (size_t i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{
	for (size_t i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}

void CPlayScene::TurnBrickIntoCoin()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		CBrick* brick = dynamic_cast<CBrick*>(objects[i]);
		if (brick != NULL)
		{
			if (brick->GetState() != BRICK_STATE_BROKEN)
				brick->TurnIntoCoin();
		}
	}
}

void CPlayScene::ShakeCamera()
{
	isCameraShake = true;
	cameraShakeStart = GetTickCount64();
}