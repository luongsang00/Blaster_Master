#include "LaserGuard.h"
CLaserGuard::CLaserGuard()
{
	SetState(LASERGUARD_STATE_WALKING_RIGHT);
}

void CLaserGuard::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + LASERGUARD_BBOX_WIDTH;

	if (state == LASERGUARD_STATE_DIE)
		bottom = y + LASERGUARD_BBOX_HEIGHT_DIE;
	else
		bottom = y + LASERGUARD_BBOX_HEIGHT;
}

void CLaserGuard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
		vx = LASERGUARD_WALKING_SPEED;
	}
	else if (x >= 480) {
		x = 480;
		vx = -LASERGUARD_WALKING_SPEED;
	}
}

void CLaserGuard::Render()
{
	if (state != STATE_DIE)
	{
		int ani = LASERGUARD_ANI;

		animation_set->at(ani)->Render(x, y);

		//RenderBoundingBox();
	}
}

void CLaserGuard::SetState(int state)
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
	case LASERGUARD_STATE_WALKING_RIGHT:
		vx = LASERGUARD_WALKING_SPEED;
		break;
	case LASERGUARD_STATE_WALKING_LEFT:
		vx = -LASERGUARD_WALKING_SPEED;
		break;
	}
}
