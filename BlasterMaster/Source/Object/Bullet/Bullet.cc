#include "Bullet.hh"
#include "Engine/Core/Game.hh"

Bullet::Bullet()
{
  m_Arrival = Game::GetInstance()->GetLastFrameTime();
}

void Bullet::Update(TimeStep elapsed)
{
  m_X += m_Velocity.GetX() * elapsed;
  m_Y += m_Velocity.GetY() * elapsed;
}
