#include "Brick.h"
#include "../GameObject/AssetIDs.h"
#include "../Scene/PlayScene.h"


void CBrick::TurnIntoCoin()
{
	CGameObject* newObj = new CCoin(x, y);
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	newObj->SetPosition(x, y);
	scene->AddObject(newObj);
	isDeleted = true;

}