#include "Drap.h"

CDrap::CDrap()
{
	SetState(STATE_IDLE);
}

void CDrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CDRAP_BBOX_WIDTH;

	if (state == CDRAP_STATE_DIE)
		bottom = y + CDRAP_BBOX_HEIGHT_DIE;
	else
		bottom = y + CDRAP_BBOX_HEIGHT;
}

void CDrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;
}

void CDrap::Render()
{
	if (state != STATE_DIE)
	{
		int ani = CDRAP_ANI;

		animation_set->at(ani)->Render(x, y);

		//RenderBoundingBox();
	}

}

void CDrap::SetState(int state)
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
