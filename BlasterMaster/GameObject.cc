#include <d3dx9.h>

#include "Debug.hh"
#include "Game.hh"
#include "GameObject.hh"
#include "Sprites.hh"

vector<LPANIMATION> CGameObject::animations;

CGameObject::CGameObject()
{
	m_X = m_Y = 0;
	m_speedX = m_speedY = 0;
	nx = 1;	
}

CGameObject::~CGameObject()
{
	// Destructors
}

void CGameObject::Update(DWORD dt)
{
	m_X += m_speedX * dt;
	m_Y += m_speedY * dt;
}

void CGameObject::Render()
{
}

void CGameObject::AddAnimation(int aniId)
{
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	animations.push_back(ani);
}
