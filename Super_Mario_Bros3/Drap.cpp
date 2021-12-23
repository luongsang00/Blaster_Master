#include "Drap.h"
CDrap::CDrap()
{
	SetState(DRAP_STATE_WALKING_LEFT);
}

void CDrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + DRAP_BBOX_WIDTH;

	if (state == DRAP_STATE_DIE)
		bottom = y + DRAP_BBOX_HEIGHT_DIE;
	else
		bottom = y + DRAP_BBOX_HEIGHT;
}

void CDrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;
	if (x <= 288)
	{
		x = 288;
		vx = DRAP_WALKING_SPEED;
	}
	else if (x >= 480) {
		x = 480;
		vx = -DRAP_WALKING_SPEED;
	}
}

void CDrap::Render()
{
	if (state != STATE_DIE)
	{
		int ani = DRAP_ANI;

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
	case DRAP_STATE_WALKING_LEFT:
		vx = -DRAP_WALKING_SPEED;
		break;
	case DRAP_STATE_WALKING_RIGHT:
		vx = DRAP_WALKING_SPEED;
		break;
	}
}
