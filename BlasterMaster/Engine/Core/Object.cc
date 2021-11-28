#include "Object.hh"

Object::Object()
{
  m_SpeedX = 0;
  m_SpeedY = 0;
  m_State = 0;
}

void Object::SetSpeed(float speedX, float speedY)
{
  m_SpeedX = speedX;
  m_SpeedY = speedY;
}

void Object::SetState(int state)
{
  m_State = state;
}

int Object::GetState()
{
  return m_State;
}

void Object::Update(TimeStep step)
{
  m_X += step * m_SpeedX;
  m_Y += step * m_SpeedY;
}
