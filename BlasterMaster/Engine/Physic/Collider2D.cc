#include "Collider2D.hh"
#include "Engine/Core/Game.hh"
#include <algorithm>

Collider2D::Collider2D(Object* refer) : m_Refer(refer)
{
  m_Velocity = m_Refer->GetVelocity();
}

Object* Collider2D::GetRefer() const
{
  return m_Refer;
}

Ref<Material> Collider2D::GetMaterial() const
{
  return m_Material;
}

Vector2F Collider2D::GetDisplacement() const
{
  return m_Displacement;
}

void Collider2D::SetMaterial(Ref<Material> material)
{
  m_Material = material;
}

void Collider2D::SetDisplacement(const Vector2F& displacement)
{
  m_Displacement = displacement;
}

void Collider2D::CalculateDisplacement(const TimeStep& elapsed)
{
  m_Displacement = Physics::CalculateDisplacement(*m_Refer, elapsed);
  m_Velocity = m_Refer->GetVelocity() + m_Refer->GetAcceleration() * elapsed;
}

void Collider2D::UpdateRefer()
{
  m_Refer->SetLocation(m_Refer->GetLocation() + m_Displacement);
  m_Refer->SetVelocity(m_Velocity);
  m_Refer->Update();
}

void Collider2D::Update(Ref<Collision2D> collision)
{
  Vector2F s = Physics::CalculateDisplacement(*m_Refer, collision->GetTime());
  // m_Displacement = m_Displacement + .4f * collision->GetNormal();
  if (collision->GetNormal().GetX())
  {
    m_Velocity.SetX(0);
    m_Displacement.SetX(s.GetX());
  }
  else
  {
    m_Velocity.SetY(0);
    m_Displacement.SetY(s.GetY());
  }
}
