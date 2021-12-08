#include "Object.hh"

Object::Object()
{
  m_SpeedX = 0;
  m_SpeedY = 0;

  m_State = 0;
  m_Died = false;
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

void Object::Die()
{
  m_Died = true; 
}

int Object::GetState()
{
  return m_State;
}

bool Object::IsDied() const
{
  return m_Died;
}

void Object::Update(TimeStep elapsed)
{
  //
}

void Object::Update(TimeStep elapsed, std::vector<Object*> objects)
{
  //
}

void Object::Render(TimeStep elapsed)
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
