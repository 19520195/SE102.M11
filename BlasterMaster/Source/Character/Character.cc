#include "Character.hh"

Character::Character()
{
  m_X = m_Y = 0;
  m_SpeedX = m_SpeedY = 0;
  m_State = 0;
}

void Character::SetPos(float X, float Y)
{
  m_X = X;
  m_Y = Y;
}

void Character::SetSpeed(float speedX, float speedY)
{
  m_SpeedX = speedX;
  m_SpeedY = speedY;
}

void Character::SetState(int state)
{
  m_State = state;
}

void Character::GetPos(float& X, float& Y)
{
  X = m_X;
  Y = m_Y;
}

void Character::GetSpeed(float& speedX, float& speedY)
{
  speedX = m_SpeedX;
  speedY = m_SpeedY;
}

int Character::GetState()
{
  return m_State;
}

void Character::Update(TimeStep step)
{
  m_X += step * m_SpeedX;
  m_Y += step * m_SpeedY;
}
