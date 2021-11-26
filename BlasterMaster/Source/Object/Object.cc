#include "Object.hh"

Object::Object()
{
  m_X = m_Y = 0;
  m_SpeedX = m_SpeedY = 0;
  m_State = 0;
}

void Object::SetPos(float X, float Y)
{
  m_X = X;
  m_Y = Y;
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

void Object::GetPos(float& X, float& Y)
{
  X = m_X;
  Y = m_Y;
}

void Object::GetSpeed(float& speedX, float& speedY)
{
  speedX = m_SpeedX;
  speedY = m_SpeedY;
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
