#include "Draw.h"
#include"Game.h"
#include"Scene.h"

Draw::Draw()
{
}

void Draw::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}
void Draw::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}