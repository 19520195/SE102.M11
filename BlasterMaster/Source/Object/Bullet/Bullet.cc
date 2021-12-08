#include "Bullet.hh"

void Bullet::Update(TimeStep elapsed)
{
  m_X += m_SpeedX * elapsed;
  m_Y += m_SpeedY * elapsed;
}
