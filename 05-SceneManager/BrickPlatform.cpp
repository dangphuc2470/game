#include "BrickPlatform.h"

#include "Sprite.h"
#include "Sprites.h"
#include "debug.h"

void CBrickPlatform::Render()
{
	CSprites * s = CSprites::GetInstance();
	//Todo: Fix the bouding box and render when length > 1 and remove this code
	if (length > 1)
		length = 1;
	s->Get(this->spriteID)->Draw(x, y);
	
	RenderBoundingBox();
	
}

void CBrickPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - (this->cellWidth  / 2); // Calculate left edge
	t = y - (this->cellHeight / 2); // Calculate top edge
	r = x + (this->cellWidth  / 2); // Calculate right edge
	b = y + (this->cellHeight / 2); // Calculate bottom edge
}

 int CBrickPlatform::IsDirectionColliable(float nx, float ny)
 {
 	if (nx == 0 && ny == -1) return 1;
 	else return 0;
 }
