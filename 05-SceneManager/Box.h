#pragma once
#include "GameObject.h"
#include "Sprites.h"
#include "AssetIDs.h"


/// <summary>
/// x, y is the center of the box, 
/// default cellWidth 87, 79 without shadow
/// default cellHeight 39
/// </summary>
class CBox1LongPink : public CGameObject {
public:
	float cellWidth; 
	float cellHeight; 
	int shadowLength = 8;
	CBox1LongPink(float x, float y, float cellWidth, float cellHeight) : CGameObject(x, y) {
	this->cellHeight = cellHeight;
	this->cellWidth = cellWidth;
	}
	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(ID_SPRITE_BOX_1_SINGLE_LONG_PINK)->Draw(x, y);

		RenderBoundingBox();
	};
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - (this->cellWidth / 2);
		t = y - (this->cellHeight / 2);
		r = l + this->cellWidth - shadowLength; //Only need to minus shadow length for the right side
		b = t + this->cellHeight;
	}

	int IsDirectionColliable(float nx, float ny)
	{
		if (nx == 0 && ny == -1) return 1;
		else return 0;
	}

};

