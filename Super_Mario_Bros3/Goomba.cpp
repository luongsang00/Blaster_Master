#include "Goomba.h"
CGoomba::CGoomba()
{
	SetState(GOOMBA_STATE_WALKING_RIGHT);
	SetState(GOOMBA_STATE_WALKING_DOWN);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (x < LEFT_LIMIT) {
		SetState(GOOMBA_STATE_WALKING_RIGHT);
	}
	else
		if (x > RIGHT_LIMIT) {
			SetState(GOOMBA_STATE_WALKING_LEFT);
		}

	if (y < TOP_LIMIT) {
		SetState(GOOMBA_STATE_WALKING_DOWN);
	}
	else
		if (y > BOTTOM_LIMIT) {
			SetState(GOOMBA_STATE_WALKING_UP);
		}
}

void CGoomba::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	/*if (state == EYE_STATE_DIE) {
		ani = EYE_ANI_DIE;
	}*/
	if (vx > 0)
		ani = GOOMBA_ANI_WALKING;
	else ani = GOOMBA_ANI_DIE;

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_WALKING_RIGHT:
		vx = GOOMBA_WALKING_SPEED;

		break;
	case GOOMBA_STATE_WALKING_LEFT:
		vx = -GOOMBA_WALKING_SPEED;

		break;
	case GOOMBA_STATE_WALKING_UP:
		vy = -GOOMBA_WALKING_SPEED;

		break;
	case GOOMBA_STATE_WALKING_DOWN:

		vy = GOOMBA_WALKING_SPEED;
	}
}
