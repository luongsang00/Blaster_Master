#include "Blue_Brick.h"

void Blue_Brick::Render()
{
	//if (state != STATE_DIE)
	{
		animation_set->at(0)->Render(x, y);
		//RenderBoundingBox();
	}
}

void Blue_Brick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (state != STATE_DIE)
	{
		l = x;
		t = y;
		r = x + BREAKABLE_BRICK_BBOX_WIDTH;
		b = y + BREAKABLE_BRICK_BBOX_HEIGHT;
	}
}