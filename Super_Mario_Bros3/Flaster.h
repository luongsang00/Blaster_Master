#pragma once
#include "GameObject.h"

#define FLASTER_WALKING_SPEED		0.15f
//0.1f
#define FLASTER_JUMP_SPEED_Y		0.5f
#define FLASTER_JUMP_DEFLECT_SPEED 0.2f
#define FLASTER_GRAVITY			0.002f
#define FLASTER_DIE_DEFLECT_SPEED	 0.5f

#define FLASTER_STATE_IDLE			0
#define FLASTER_STATE_WALKING_RIGHT	100
#define FLASTER_STATE_WALKING_LEFT	200
#define FLASTER_STATE_WALKING_UP	500
#define FLASTER_STATE_WALKING_DOWN	600
#define FLASTER_STATE_JUMP			300
#define FLASTER_STATE_DIE				400

#define FLASTER_ANI_BIG_IDLE_RIGHT			0
#define FLASTER_ANI_BIG_IDLE_LEFT			1
#define FLASTER_ANI_BIG_IDLE_TOP			2
#define FLASTER_ANI_BIG_IDLE_BUTTOM			3
#define FLASTER_ANI_SMALL_IDLE_RIGHT		4
#define FLASTER_ANI_SMALL_IDLE_LEFT			5

#define FLASTER_ANI_BIG_WALKING_RIGHT		6
#define FLASTER_ANI_BIG_WALKING_LEFT		7
#define FLASTER_ANI_BIG_WALKING_TOP			8
#define FLASTER_ANI_BIG_WALKING_BUTTOM		9
#define FLASTER_ANI_SMALL_WALKING_RIGHT		10
#define FLASTER_ANI_SMALL_WALKING_LEFT		11


#define FLASTER_ANI_DIE				12

#define	FLASTER_LEVEL_SMALL	1
#define	FLASTER_LEVEL_BIG		2

#define FLASTER_BIG_BBOX_WIDTH  15
#define FLASTER_BIG_BBOX_HEIGHT 27

#define FLASTER_SMALL_BBOX_WIDTH  13
#define FLASTER_SMALL_BBOX_HEIGHT 15

#define FLASTER_UNTOUCHABLE_TIME 5000



class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y;
public:
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};