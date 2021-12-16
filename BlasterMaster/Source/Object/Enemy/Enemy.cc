#include "Enemy.hh"

Box2F Enemy::GetActiveZone() const
{
  return m_ActiveZone;
}

bool Enemy::IsActivated() const
{
  return m_IsActived;
}

void Enemy::SetStartPoint(const Vector2F& point)
{
  m_StartPoint = point;
  m_X = point.GetX();
  m_Y = point.GetY();
}

void Enemy::SetActiveZone(const Box2F& activeZone)
{
  m_ActiveZone = activeZone; 
}

void Enemy::Activate()
{
  m_IsActived = true;
}

void Enemy::Deactivate()
{
  m_IsActived = false;
}

Enemy* Enemy::Create(const std::string& name)
{
  if (name == "Interrupt" ) return new Interrupt();
  if (name == "Ballbot"   ) return new Ballbot();
  if (name == "Stuka"     ) return new Stuka();
  if (name == "Eyelet"    ) return new Eyelet();
  if (name == "Ball-Carry") return new BallCarry();
  return nullptr;
}
