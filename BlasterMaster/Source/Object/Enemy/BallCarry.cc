#include "BallCarry.hh"
#include "Engine/Core/Game.hh"
#include "Scene/PlayScene.hh"
#include "Object/Brick.hh"
#include "Object/Bullet/BallCarryBullet.hh"

constexpr float BALLCARRY_SPEED = 0.04f;

BallCarry::BallCarry()
{
  m_LastShootTime = 0;
  m_WalkState = BallCarryWalkState::Shoot;
  m_PrevWalkState = BallCarryWalkState::Shoot;
  SetWalkState(BallCarryWalkState::Left);
}

void BallCarry::SetWalkState(BallCarryWalkState ws)
{
  if (m_WalkState != ws)
  {
    m_PrevWalkState = m_WalkState;
    switch (m_WalkState = ws)
    {
    case BallCarryWalkState::Left:
      SetAnimation("Ball-Carry-Walk");
      m_Velocity.SetX(-BALLCARRY_SPEED);
      break;

    case BallCarryWalkState::Right:
      SetAnimation("Ball-Carry-Walk");
      m_Velocity.SetX(BALLCARRY_SPEED);
      break;

    case BallCarryWalkState::Shoot:
      SetSprite("Ball-Carry-Idle");
      m_Velocity.SetX(0);
      break;
    }
  }
}

void BallCarry::OnCollide(const Ref<Collision2D>& collison)
{
  auto refer = collison->GetCollider()->GetRefer();
  if (dynamic_cast<Brick*>(refer))
  {
    if (m_Velocity.GetX() > 0)
      SetWalkState(BallCarryWalkState::Left);
    else SetWalkState(BallCarryWalkState::Right);
  }
}

void BallCarry::Update()
{
  TimeStep current = Game::GetInstance()->GetLastFrameTime();
  if (m_WalkState == BallCarryWalkState::Shoot)
  {
    if (current - m_LastShootTime > 400)
      SetSprite("Ball-Carry-Active");
    if (current - m_LastShootTime > 800)
      SetSprite("Ball-Carry-Idle");
    if (current - m_LastShootTime > 1200)
      SetWalkState(m_PrevWalkState);
  }
  else if (current - m_LastShootTime > 5000)
  {
    auto scene = std::static_pointer_cast<PlayScene>(
      Game::GetInstance()->GetScene());
    auto player = scene->GetPlayer();
    
    if ((player->GetCenter() - this->GetCenter()).Abs() < 32)
    {
      m_LastShootTime = current;
      SetWalkState(BallCarryWalkState::Shoot);
      for (float i = -2; i <= 1; i += 1)
      {
        auto bullet = CreateRef<BallCarryBullet>();
        Vector2F location = this->GetCenter() + Vector2F(i * 3, 12.f);
        bullet->SetLocation(location);
        bullet->SetAcceleration(Vector2F(0, Physics::GRAVITY));
        bullet->SetVelocity(Vector2F(i * 0.02f, Physics::GRAVITY * -222.f));
        scene->AddObject(bullet);
      }
    }
  }
}
