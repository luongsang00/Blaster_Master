#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Tank_Body.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"

CTank_Body::CTank_Body(float x, float y) : CGameObject()
{
	level = FLASTER_LEVEL_BIG;
	untouchable = 0;
	SetState(TANK_BODY_STATE_IDLE);

	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CTank_Body::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	/*vy += MARIO_GRAVITY * dt;*/

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != TANK_BODY_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > FLASTER_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			/*if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -TANK_BODY_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (level > FLASTER_LEVEL_SMALL)
							{
								level = FLASTER_LEVEL_SMALL;
								StartUntouchable();
							}
							else
								SetState(TANK_BODY_STATE_DIE);
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}*/
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CTank_Body::Render()
{
	int ani = -1;
	if (state == TANK_BODY_STATE_DIE)
		ani = FLASTER_ANI_DIE;
	else
		if (level == FLASTER_LEVEL_BIG)
		{
			/*if (vx == 0)
			{
				if (nx > 0) ani = FLASTER_ANI_BIG_IDLE_RIGHT;
				else ani = FLASTER_ANI_BIG_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = FLASTER_ANI_BIG_WALKING_RIGHT;
			else if(vx<0) ani = FLASTER_ANI_BIG_WALKING_LEFT;
			else if (vy == 0)
			{
				if (ny > 0) ani = FLASTER_ANI_BIG_IDLE_BUTTOM;
				else ani = FLASTER_ANI_BIG_IDLE_TOP;
			}
			else if(vy > 0)
				ani = FLASTER_ANI_BIG_WALKING_BUTTOM;
			else if(vy <0)
				ani = FLASTER_ANI_BIG_WALKING_TOP;*/
			switch (nx)
			{
			case 1:
				ani = TANK_BODY_ANI_BIG_IDLE_RIGHT;
				break;
			case -1:
				ani = TANK_BODY_ANI_BIG_IDLE_LEFT;
				break;
			case 0:
				ani = TANK_BODY_ANI_BIG_IDLE_DOW;
				break;
			case 2:
				ani = TANK_BODY_ANI_BIG_IDLE_UP;
				break;
			}
			if (vx > 0)
				ani = TANK_BODY_ANI_BIG_WALKING_RIGHT;
			else if (vx < 0) 
				ani = TANK_BODY_ANI_BIG_WALKING_LEFT;
			else if (vy > 0)
				ani = TANK_BODY_ANI_BIG_WALKING_DOW;
			else if (vy < 0)
				ani = TANK_BODY_ANI_BIG_WALKING_UP;
			
		}
		else if (level == FLASTER_LEVEL_SMALL)
		{
			if (vx == 0)
			{
				if (nx > 0) ani = FLASTER_ANI_SMALL_IDLE_RIGHT;
				else ani = FLASTER_ANI_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
				ani = FLASTER_ANI_SMALL_WALKING_RIGHT;
			else ani = FLASTER_ANI_SMALL_WALKING_LEFT;
		}

	int alpha = 255;
	if (untouchable) alpha = 128;

	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
}

void CTank_Body::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case TANK_BODY_STATE_WALKING_DOWN:
		vy = TANK_BODY_WALKING_SPEED;
		nx = 0;
		break;
	case TANK_BODY_STATE_WALKING_UP:
		vy = -TANK_BODY_WALKING_SPEED;
		nx = 2;
		break;
	case TANK_BODY_STATE_WALKING_RIGHT:
		vx = TANK_BODY_WALKING_SPEED;
		nx = 1;
		break;
	case TANK_BODY_STATE_WALKING_LEFT:
		vx = -TANK_BODY_WALKING_SPEED;
		nx = -1;
		break;
	case TANK_BODY_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		vy = -TANK_BODY_JUMP_SPEED_Y;
		break;
	case TANK_BODY_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case TANK_BODY_STATE_DIE:
		vy = -TANK_BODY_DIE_DEFLECT_SPEED;
		break;
	}
}

void CTank_Body::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	if (level == FLASTER_LEVEL_BIG)
	{
		right = x + FLASTER_BIG_BBOX_WIDTH;
		bottom = y + FLASTER_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + FLASTER_SMALL_BBOX_WIDTH;
		bottom = y + FLASTER_SMALL_BBOX_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CTank_Body::Reset()
{
	SetState(TANK_BODY_STATE_IDLE);
	SetLevel(FLASTER_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

