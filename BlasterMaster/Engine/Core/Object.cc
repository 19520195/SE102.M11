#include "Object.hh"
#include "Engine/Math/Physic.hh"

Object::Object()
{
  m_State = 0;
  m_Died = false;
}

void Object::SetSpeed(float speedX, float speedY)
{
  m_Velocity = Vector2F(speedX, speedY);
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
  // Calculate displacement based on velocity and acceleration
  Vector2F deltaDisplacement = Physic::CalculateDisplacement(
    static_cast<float>(elapsed),
    m_Velocity,
    m_Acceleration);

  // Update location with calculated displacement
  Vector2F& location = (*static_cast<Vector2F*>(this));
  location = location + deltaDisplacement;

  // Dis-Comment
  m_Velocity = m_Acceleration * static_cast<float>(elapsed);
}

void Object::Update(TimeStep elapsed, std::vector<Object*> objects)
{
  Update(elapsed);
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
