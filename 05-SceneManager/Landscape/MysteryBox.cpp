#include "MysteryBox.h"

void CMysteryBox::SetState(int state)
{
	if (this->state == MBOX_STATE_NORMAL && state == MBOX_STATE_UNBOX)
	{
		//coin++;

		CGameObject* newObj = NULL;
		switch (objectToSpawn)
		{
		case OBJECT_TYPE_GOOMBA:
			newObj = new CGoomba(x, y);
			break;
		case OBJECT_TYPE_MUSHROOM:
			newObj = new CMushroom(x, y);
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
		if (newObj != NULL)
		{
			CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
			newObj->SetPosition(x, y - 30);
			scene->AddObject(newObj);
		}
	};
	CGameObject::SetState(state);
}