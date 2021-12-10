#include "Enemy.hh"

void Enemy::SetStartPoint(const Vector2D& point)
{
  m_StartPoint = point;
  m_X = point.GetX();
  m_Y = point.GetY();
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
