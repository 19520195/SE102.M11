#pragma once
#include "GameObject.hh"

#define JASON_WALKING_SPEED		0.1f
#define JASON_JUMP_SPEED_Y		0.5f
#define JASON_GRAVITY					0.1f

#define JASON_STATE_IDLE					0
#define JASON_STATE_WALKING_RIGHT	100
#define JASON_STATE_WALKING_LEFT	200
#define JASON_STATE_WALKING_UP		300
#define JASON_STATE_WALKING_DOWN  400

#define JASON_STATE_JUMP					500

#define JASON_ANI_IDLE_RIGHT		0
#define JASON_ANI_IDLE_LEFT			1
#define JASON_ANI_WALKING_RIGHT		2
#define JASON_ANI_WALKING_LEFT		3

class CJason : public CGameObject
{
public:
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};