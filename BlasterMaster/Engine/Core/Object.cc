#include "Object.hh"
#include "Engine/Math/Physic.hh"

Object::Object()
{
  m_State = 0;
  m_Died = false;
  m_Collider = CreateRef<Collider2D>(this);
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

Ref<Collider2D> Object::GetCollider() const
{
  return m_Collider;
}

bool Object::IsDied() const
{
  return m_Died;
}

void Object::SetSprite(const std::string& name)
{
  m_Render = SpriteBase::GetInstance()->Get(name);
}

void Object::SetAnimation(const std::string& name)
{
  m_Render = AnimationBase::GetInstance()->Get(name);
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

void Object::Update(TimeStep elapsed, std::vector<Ref<Object>> objects)
{
  Update(elapsed);
}

void Object::Render(TimeStep elapsed)
{
  if (m_Render) m_Render->Render(m_X, m_Y, elapsed);
}
