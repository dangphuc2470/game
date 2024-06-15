
#pragma once
#include "../GameObject/GameObject.h"
#include "../Game/Animation.h"
#include "../Game/Animations.h"
#include "../Mario.h"
#include "../GameObject/AssetIDs.h"
#include "../Scene/PlayScene.h"
#include "../Enemy/Goomba.h"
#include <stdio.h>
#include <map>

#define MBOX_BBOX_WIDTH 14
#define MBOX_BBOX_HEIGHT 15
#define MBOX_STATE_NORMAL 100
#define MBOX_STATE_UNBOX 200

class CMysteryBox : public CGameObject {
public:
	int objectToSpawn;
	CMysteryBox(float x, float y, bool isOpenable, int objectToSpawn) : CGameObject(x, y) {
	if (isOpenable)
		state = MBOX_STATE_NORMAL;
	else
		state = MBOX_STATE_UNBOX;
	this->objectToSpawn = objectToSpawn;
	}
	void Render()
	{
		//DebugOutTitle(L"MBOX state: %d\n", state);
		if (state == MBOX_STATE_UNBOX)
		{
			CSprites* sprites = CSprites::GetInstance();
			sprites->Get(ID_SPRITE_MYSTERY_BOX_UNBOX)->Draw(x, y);
		}
		else
		{
			CAnimations* animations = CAnimations::GetInstance();
			animations->Get(ID_ANI_MYSTERY_BOX)->Render(x, y);
		}
		//RenderBoundingBox();
	};

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
		
		CGameObject::Update(dt);
		CCollision::GetInstance()->Process(this, dt, coObjects);
	};

	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - MBOX_BBOX_WIDTH / 2;
		t = y - MBOX_BBOX_HEIGHT / 2;
		r = l + MBOX_BBOX_WIDTH;
		b = t + MBOX_BBOX_HEIGHT;
	};

	void SetState(int state) {
		if (this->state == MBOX_STATE_NORMAL && state == MBOX_STATE_UNBOX)
		{
			//coin++;

			CGameObject* newObj = NULL;
			switch (objectToSpawn)
			{
				case OBJECT_TYPE_GOOMBA:
					newObj = new CGoomba(x, y);
					break;
				case -1:
					return;
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
			if (newObj == NULL) return;
			CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
			newObj->SetPosition(x, y - 30);
			scene->AddObject(newObj);
		};
		CGameObject::SetState(state);
	}

};