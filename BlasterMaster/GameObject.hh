#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.hh"


using namespace std;

class CGameObject
{
protected:
	float m_X;
	float m_Y;

	float m_speedX;
	float m_speedY;

	int nx;	 

	int state;									

	static vector<LPANIMATION> animations;

public:
	CGameObject();
	~CGameObject();

	void SetPosition(float x, float y) { this->m_X = x, this->m_Y = y; }

	void SetSpeed(float speedX, float speedY) { this->m_speedX = speedX, this->m_speedY = speedY; }

	void SetState(int state) { this->state = state; }

	int GetState() { return this->state; }

	static void AddAnimation(int aniId);

	void Update(DWORD dt);
	
	void Render();
};