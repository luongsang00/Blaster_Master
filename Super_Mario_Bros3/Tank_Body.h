#pragma once
#include "GameObject.h"

#define TANK_BODY_WALKING_SPEED		 0.15f
//0.1f
#define TANK_BODY_JUMP_SPEED_Y		 0.5f
#define TANK_BODY_JUMP_DEFLECT_SPEED	 0.2f
#define TANK_BODY_GRAVITY				 0.002f
#define TANK_BODY_DIE_DEFLECT_SPEED	 0.5f

#define TANK_BODY_STATE_IDLE			0
#define TANK_BODY_STATE_WALKING_RIGHT	100
#define TANK_BODY_STATE_WALKING_LEFT	200
#define TANK_BODY_STATE_WALKING_UP	500
#define TANK_BODY_STATE_WALKING_DOWN	600
#define TANK_BODY_STATE_JUMP			300
#define TANK_BODY_STATE_DIE				400

#define TANK_BODY_ANI_BIG_IDLE_RIGHT			0
#define TANK_BODY_ANI_BIG_IDLE_LEFT			1
#define TANK_BODY_ANI_BIG_IDLE_UP			2
#define TANK_BODY_ANI_BIG_IDLE_DOW			3
#define FLASTER_ANI_SMALL_IDLE_RIGHT		4
#define FLASTER_ANI_SMALL_IDLE_LEFT			5

#define TANK_BODY_ANI_BIG_WALKING_RIGHT		6
#define TANK_BODY_ANI_BIG_WALKING_LEFT		7
#define TANK_BODY_ANI_BIG_WALKING_UP			8
#define TANK_BODY_ANI_BIG_WALKING_DOW		9
#define FLASTER_ANI_SMALL_WALKING_RIGHT		10
#define FLASTER_ANI_SMALL_WALKING_LEFT		11


#define FLASTER_ANI_DIE				12

#define	FLASTER_LEVEL_SMALL		1
#define	FLASTER_LEVEL_BIG		2

#define FLASTER_BIG_BBOX_WIDTH  15
#define FLASTER_BIG_BBOX_HEIGHT 10

#define FLASTER_SMALL_BBOX_WIDTH  13
#define FLASTER_SMALL_BBOX_HEIGHT 15

#define FLASTER_UNTOUCHABLE_TIME 5000



class CTank_Body : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
public:
	CTank_Body(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};