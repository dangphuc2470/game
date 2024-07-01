#include "MysteryBox.h"

void CMysteryBox::SetState(int state)
{
	
		//if (dynamic_cast<CMushroom*>(objectSpawned))
		//{
		//	CMushroom* mushroom = dynamic_cast<CMushroom*>(objectSpawned);
		//	//mushroom->SetState(MUSHROOM_STATE_MOVING_UP);
		//}
		//
	
	CGameObject::SetState(state);
}

CMysteryBox::CMysteryBox(float x, float y, bool isOpenable, int objectToSpawn, bool isBrick)
{
		switch (objectToSpawn)
		{
		case OBJECT_TYPE_GOOMBA:
			objectSpawned = new CGoomba(x, y);
			break;
		case OBJECT_TYPE_MUSHROOM:
			objectSpawned = new CMushroom(x, y);
			break;
		case OBJECT_TYPE_MUSHROOM_GREEN:
			objectSpawned = new CMushroom(x, y, false);
			break;
		default:
			break;
			/*case ID_OBJECT_MUSHROOM:
				obj = new CMushroom(x, y);
				break;
			case ID_OBJECT_FLOWER:
				obj = new CFlower(x, y);
				break;
			case ID_OBJECT_COIN:
				obj = new CCoin(x, y);
				break;*/
		}
		// Add new object to the scene
		if (objectSpawned != NULL)
		{
			CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
			objectSpawned->SetPosition(x, y);
			scene->AddObject(objectSpawned);
		}
		this->isBrick = isBrick;
		if (isOpenable)
			state = MBOX_STATE_NORMAL;
		else
			state = MBOX_STATE_UNBOX;
		this->objectToSpawn = objectToSpawn;
}