#pragma once
#include "../GameObject/GameObject.h"
#include "../Game/Sprites.h"
#include "../GameObject/AssetIDs.h"

class CBoxPlatform : public CGameObject {
public:
	float cellWidth;
	float cellHeight;
	int spriteID;
	int shadowLength = 8;
	CBoxPlatform(float x, float y, float cellWidth, float cellHeight, int spriteID) : CGameObject(x, y) {
		//Set default cell size for each sprite
		switch (spriteID)
		{
		case ID_SPRITE_BOX_PLATFORM_SQUARE_PINK:
			this->cellWidth = 55;
			this->cellHeight = 48;
			break;
		case ID_SPRITE_BOX_PLATFORM_RECTANGLE_PINK_GROUND_HORIZONTAL:
			this->cellWidth = 63;
			this->cellHeight = 32;
			break;
		case ID_SPRITE_BOX_PLATFORM_RECTANGLE_PINK_SKY_HORIZONTAL:
			this->cellWidth = 87;
			this->cellHeight = 40;
			break;
		case ID_SPRITE_BOX_PLATFORM_RECTANGLE_PINK_LARGE_HORIZONTAL:
			this->cellWidth = 119;
			this->cellHeight = 64;
			break;
		case ID_SPRITE_BOX_PLATFORM_GREEN_SHORT_HORIZONTAL:
			this->cellWidth = 71;
			this->cellHeight = 40;
			break;
		case ID_SPRITE_BOX_PLATFORM_GREEN_SHORT_FAT_HORIZONTAL:
			this->cellWidth = 87;
			this->cellHeight = 48;
			break;
		case ID_SPRITE_BOX_PLATFORM_GREEN_LONG_HORIZONTAL:
			this->cellWidth = 103;
			this->cellHeight = 32;
			break;
		case ID_SPRITE_BOX_PLATFORM_GREEN_LONG_VERTICAL:
			this->cellWidth = 55;
			this->cellHeight = 144;
			break;
		case ID_SPRITE_BOX_PLATFORM_BLUE_TALL:
			this->cellWidth = 55;
			this->cellHeight = 80;
			break;
		case ID_SPRITE_BOX_PLATFORM_BLUE_FAT:
			this->cellWidth = 119;
			this->cellHeight = 96;
			break;
		case ID_SPRITE_BOX_PLATFORM_BLUE_SHORT:
			this->cellWidth = 71;
			this->cellHeight = 40;
			break;
		case ID_SPRITE_BOX_PLATFORM_WHITE_TALL:
			this->cellWidth = 71;
			this->cellHeight = 112;
			break;
		case ID_SPRITE_BOX_PLATFORM_RECTANGLE_PINK_TALL_VERTICAL:
			this->cellWidth = 71;
			this->cellHeight = 80;
			break;
			

		default:
			this->cellWidth = 0;
			this->cellHeight = 0;
			break;
		}


		if (cellWidth != 0)
			this->cellWidth = cellWidth;
		if (cellHeight != 0)
			this->cellHeight = cellHeight;
		this->spriteID = spriteID;

	}

	void Render()
	{
		CSprites* s = CSprites::GetInstance();
		s->Get(spriteID)->Draw(x, y);
		//RenderBoundingBox();
	};

	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b)
	{
		l = x - (this->cellWidth / 2);
		t = y - (this->cellHeight / 2);
		r = l + this->cellWidth - shadowLength; //Only need to minus shadow length for the right side
		b = t + this->cellHeight;
		this->top = t;
		this->bottom = b;
	}

	int IsDirectionColliable(float nx, float ny)
	{
		if (nx == 0 && ny == -1) return 1;
		else return 0;
	}

};



