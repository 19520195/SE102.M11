#include "Bullet.hh"

void Bullet::Update(TimeStep elapsed)
{
  m_X += m_Velocity.GetX() * elapsed;
  m_Y += m_Velocity.GetY() * elapsed;
}
