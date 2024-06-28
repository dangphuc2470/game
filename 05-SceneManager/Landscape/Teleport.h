#pragma once
#include "../GameObject/GameObject.h"
#include "../GameObject/AssetIDs.h"
class CTeleport : public CGameObject
{
	float size = 15;
	float targetX, targetY;
public:
	CTeleport(float x, float y, float targetX, float targetY) : CGameObject(x, y) 
	{
		this->targetX = targetX;
		this->targetY = targetY;
	}
	void Render()
	{
		RenderBoundingBox();
	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b) {
		l = x - size / 2;
		t = y - size / 2;
		r = l + size;
		b = t + size;
	};
	int IsBlocking() { return 0; }

	void GetTarget(float& x, float& y) {
		x = targetX;
		y = targetY;
	}
};