#pragma once

#include "../GameObject/GameObject.h"
#include "../Game/Animation.h"
#include "../Game/Animations.h"

#define BRICK_BBOX_WIDTH 15
#define BRICK_BBOX_HEIGHT 15

class CBrick : public CGameObject {
public:
	CBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};