#include "LazerGuard.hh"
#include "Object/Brick.hh"

constexpr float LAZER_GUARD_VELOCITY = 0.1f;

LazerGuard::LazerGuard()
{
  SetWalkState(LazerGuardWalkState::Left);
}

void LazerGuard::SetWalkState(const LazerGuardWalkState& ws)
{
  switch (m_WalkState = ws)
  {
  case LazerGuardWalkState::Left:
    m_Velocity.SetX(-LAZER_GUARD_VELOCITY);
    SetAnimation("Lazer-Guard-Walk-Left");
    break;

  case LazerGuardWalkState::Right:
    m_Velocity.SetX(LAZER_GUARD_VELOCITY);
    SetAnimation("Lazer-Guard-Walk-Right");
    break;
  }
}

void LazerGuard::OnCollide(const Ref<Collision2D>& collision)
{
  if (dynamic_cast<Brick*>(collision->GetCollider()->GetRefer()))
  {
    if (collision->GetNormal().GetX() > 0)
      SetWalkState(LazerGuardWalkState::Right);
    else SetWalkState(LazerGuardWalkState::Left);
  }
}

void LazerGuard::Update()
{
  //
}
