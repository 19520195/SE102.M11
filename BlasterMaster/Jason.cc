#include "Jason.hh"

void CJason::Update(DWORD dt)
{
	CGameObject::Update(dt);

	// simple fall down
	//m_speedY += JASON_GRAVITY;
	//if (m_Y > 100) 
	//{
	//	m_speedY = 0; m_Y = 100.0f;
	//}

	// simple screen edge collision!!!
	if (m_speedX > 0 && m_X > 290) m_X = 290;
	if (m_speedX < 0 && m_X < 0) m_X = 0;
}

void CJason::Render()
{
	int ani;
	if (m_speedX == 0)
	{
		if (nx>0) ani = JASON_ANI_IDLE_RIGHT;
		else ani = JASON_ANI_IDLE_LEFT;
	}
	else if (m_speedX > 0) 
		ani = JASON_ANI_WALKING_RIGHT; 
	else ani = JASON_ANI_WALKING_LEFT;

	animations[ani]->Render(m_X, m_Y);
}

void CJason::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case JASON_STATE_WALKING_RIGHT:
		m_speedX = JASON_WALKING_SPEED;
		nx = 1;
		break;

	case JASON_STATE_WALKING_LEFT:
		m_speedX = -JASON_WALKING_SPEED;
		nx = -1;
		break;

	case JASON_STATE_WALKING_DOWN:
		m_speedY = JASON_WALKING_SPEED;
		nx = 1;
		break;

	case JASON_STATE_WALKING_UP:
		m_speedY = -JASON_WALKING_SPEED;
		nx = -1;
		break;

	case JASON_STATE_JUMP: 
		if (m_Y == 100)
			m_speedY = -JASON_JUMP_SPEED_Y;

	case JASON_STATE_IDLE: 
		m_speedX = 0;
		m_speedY = 0;
		break;
	}
}
