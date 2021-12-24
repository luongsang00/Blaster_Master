#include "GX_680.h"

CGX_680::CGX_680()
{
	SetState(STATE_IDLE);
}

void CGX_680::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CGX680_BBOX_WIDTH;

	if (state == CGX680_STATE_DIE)
		bottom = y + CGX680_BBOX_HEIGHT_DIE;
	else
		bottom = y + CGX680_BBOX_HEIGHT;
}

void CGX_680::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;
}

void CGX_680::Render()
{
	if (state != STATE_DIE)
	{
		int ani = CGX680_ANI;

		animation_set->at(ani)->Render(x, y);

		//RenderBoundingBox();
	}
}

void CGX_680::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case STATE_DIE:
		vy = DIE_PULL;
		break;
	}
}
