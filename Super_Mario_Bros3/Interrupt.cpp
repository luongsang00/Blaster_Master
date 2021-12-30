#include "Interrupt.h"
CInterrupt::CInterrupt()
{
	SetState(STATE_IDLE);
}

void CInterrupt::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CINTERRUPT_BBOX_WIDTH;

	if (state == CINTERRUPT_STATE_DIE)
		bottom = y + CINTERRUPT_BBOX_HEIGHT_DIE;
	else
		bottom = y + CINTERRUPT_BBOX_HEIGHT;
}

void CInterrupt::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CPlayScene* playscene = ((CPlayScene*)CGame::GetInstance()->GetCurrentScene());
	CGameObject::Update(dt, coObjects);

	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	if (!spammed && state == STATE_DIE)
	{
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->AddKaboomMng(x, y);
		int chance = rand() % 100;
		srand(time(NULL));
		if (chance >= 70)
			playscene->AddItemsMng(x, y, 0);
		spammed = true;
	}

	x += dx;
	y += dy;

	float px, py;

	if (state != STATE_DIE)
	{
		((CPlayScene*)CGame::GetInstance()->GetCurrentScene())->GetPlayer()->GetPosition(px, py);
		if (state != CINTERRUPT_STATE_OPEN)
			if (this->x < px + SOPHIA_BIG_BBOX_WIDTH && this->x + CINTERRUPT_BBOX_WIDTH >= px && this->y < py)
			{
				SetState(CINTERRUPT_STATE_OPEN);
				playscene->AddInterruptBulletMng(this->x, this->y);
			}
	}
}

void CInterrupt::Render()
{
	if (state != STATE_DIE)
	{
		int ani = CINTERRUPT_ANI_IDLE;
		switch (state)
		{
		case CINTERRUPT_STATE_OPEN:
			ani = CINTERRUPT_ANI_OPEN;
			break;
		}

		animation_set->at(ani)->Render(x, y);

		//RenderBoundingBox();
	}
}

void CInterrupt::SetState(int state)
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
