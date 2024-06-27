#include "Spawner.h"
#include "../Scene/PlayScene.h"
void CSpawner::Spawn(CGameObject* player)
{
	CMario * mario = dynamic_cast<CMario*>(player);
	CGameObject* newObj;
	switch (type)
	{
	case OBJECT_TYPE_GOOMBA:
		newObj = new CGoomba(objX, objY);
		break;
	case OBJECT_TYPE_GOOMBA_WINGS:
		newObj = new CGoomba(objX, objY, true);
		break;
	case OBJECT_TYPE_KOOPA_GREEN:
		newObj = new CKoopa(objX, objY, true, false, mario);
		break;
	case OBJECT_TYPE_KOOPA_GREEN_WINGS:
		newObj = new CKoopa(objX, objY, true, true, mario);
		break;
	default:
		newObj = new CBrick(objX, objY);
		break;
	}

	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	newObj->SetPosition(objX, objY);
	scene->AddObject(newObj);

	//if (type == 1)
	//	// Create new object
	//{
	//	float x = 900, y = 150;
	//	CGameObject* newObj = new CGoomba(x, y);


	//	// Add new object to the scene
	//	

	//}
	//else
	//{
	//	float x = 1325, y = 90;
	//	CGameObject* newObj = new CKoopa(x, y, true, true);
	//	CGameObject* newObj2 = new CKoopa(x + 25, y - 10, true, true);
	//	CGameObject* newObj3 = new CKoopa(x + 45, y - 20, true, true);
	//	CGameObject* newObj4 = new CKoopa(x + 125, y + 90, true, false);

	//	// Add new object to the scene
	//	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
	//	//scene->AddObject(newObj);
	//	newObj->SetPosition(x, y);
	//	newObj2->SetPosition(x + 50, y);
	//	newObj3->SetPosition(x + 100, y);
	//	newObj4->SetPosition(x + 150, y);

	//	scene->AddObject(newObj);
	//	scene->AddObject(newObj2);
	//	scene->AddObject(newObj3);
	//	scene->AddObject(newObj4);
	//}
}
