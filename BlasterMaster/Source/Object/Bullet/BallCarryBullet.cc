#include "BallCarryBullet.hh"
#include "Object/Brick.hh"
#include "Object/Player/Player.hh"
#include "Engine/Core/Game.hh"

BallCarryBullet::BallCarryBullet()
{
  SetSprite("Ball-Carry-Bullet");
}

bool BallCarryBullet::IsDied() const
{
  TimeStep current = Game::GetInstance()->GetLastFrameTime();
  return (current - m_Arrival) > 3000 || Bullet::IsDied();
}

void BallCarryBullet::OnCollide(const Ref<Collision2D>& collison)
{
  auto refer = collison->GetCollider()->GetRefer();
  if (dynamic_cast<Brick*>(refer))
  {
    m_Velocity = 0;
  }

  if (dynamic_cast<Player*>(refer))
    DEBUG_MSG(L"Damged to Player\n");
}
