#include "Spawner.h"
#include "../Scene/PlayScene.h"
void CSpawner::Spawn()
{
		// Create new object
	float x = 900, y = 150;
		CGameObject* newObj = new CGoomba(x, y);
		CGameObject* newObj2 = new CGoomba(x + 50, y);
		CGameObject* newObj3 = new CGoomba(x + 100, y, true);

		// Add new object to the scene
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		//scene->AddObject(newObj);
		newObj->SetPosition(x, y);
		newObj2->SetPosition(x + 50, y);
		newObj3->SetPosition(x + 100, y);

		scene->AddObject(newObj);
		scene->AddObject(newObj2);
		scene->AddObject(newObj3);
	
}
