#pragma once
#include "../GameObject/GameObject.h"
#include "../Game/Textures.h"
#include "../Enemy/Goomba.h"
#include "../Enemy/Koopa.h"

#define SPAWNER_BBOX_WIDTH 1
#define SPAWNER_BBOX_HEIGHT 200
class CSpawner : public CGameObject {
	protected:
	int type;
	float objX, objY;
public:
	CSpawner(float x, float y, int type, float objX, float objY) : CGameObject(x, y) {
		this->type = type;
		this->objX = objX;
		this->objY = objY;
	}

	void Render() {
		RenderBoundingBox();
	}
	
	virtual void Spawn(CGameObject* player);

	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - SPAWNER_BBOX_WIDTH / 2;
		t = y - SPAWNER_BBOX_HEIGHT / 2;
		r = l + SPAWNER_BBOX_WIDTH;
		b = t + SPAWNER_BBOX_HEIGHT;
	};
	int IsBlocking() { return 0; }
};
