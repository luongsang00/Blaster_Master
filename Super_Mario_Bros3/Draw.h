#pragma once
#include "GameObject.h"
#define NoCollisionObject_TYPE_NORMAL	1
#define NoCollisionObject_TYPE_NUMBER_THREE	2
#define NoCollisionObject_TYPE_BUSH_INTRO_SCENE	3
class Draw : public CGameObject
{
	bool isRender;
	int type;
public:
	Draw();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
