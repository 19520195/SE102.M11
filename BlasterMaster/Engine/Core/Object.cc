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
  //
}

void Object::Update(TimeStep step, std::vector<Object*> objects)
{
  //
}

void SpriteObject::Render(float X, float Y, TimeStep elapsed)
{
  SpriteBase::GetInstance()->Get(m_ID)->Render(X, Y);
}

void SpriteObject::Render(TimeStep elapsed)
{
  Render(m_X, m_Y, elapsed);
}

void AnimationObject::Render(float X, float Y, TimeStep elapsed)
{
  AnimationBase::GetInstance()->Get(m_ID)->Render(X, Y, elapsed);
}

void AnimationObject::Render(TimeStep elapsed)
{
  Render(m_X, m_Y, elapsed);
}
