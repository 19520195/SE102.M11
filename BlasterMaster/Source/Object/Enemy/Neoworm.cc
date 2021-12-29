#include "Neoworm.hh"
#include "Engine/Core/Game.hh"
#include "Scene/PlayScene.hh"

Neoworm::Neoworm(Vector2F p)
{
  m_X = p.GetX();
  m_Y = p.GetY();

  m_Width = NEOWORMFALL_WIDTH;
  m_Height = NEOWORMFALL_HEIGHT;
  m_Acceleration = Vector2F(0.f, Physics::GRAVITY);
  m_Render = SpriteBase::GetInstance()->Get("Neoworm-Fall");
}

void Neoworm::SetWalkState(NeowormWalkState ws)
{
  switch (m_WalkState = ws)
  {
  case NeowormWalkState::Left:
    m_Velocity.SetX(-NEOWORMFALL_SPEED);
    SetAnimation("Neoworm-Walk-Left");
    break;

  case NeowormWalkState::Right:
    m_Velocity.SetX(NEOWORMFALL_SPEED);
    SetAnimation("Neoworm-Walk-Right");
    break;
  }
}

void Neoworm::OnCollide(const Ref<Collision2D>& collision)
{
  auto refer = collision->GetCollider()->GetRefer();
  if (IsTriggered() == false)
    if (dynamic_cast<Player*>(refer) || dynamic_cast<Brick*>(refer))
      return this->Activate();

  if (dynamic_cast<Brick*>(refer) && collision->GetNormal().GetX())
  {
    if (m_WalkState == NeowormWalkState::Left)
      SetWalkState(NeowormWalkState::Right);
    else SetWalkState(NeowormWalkState::Left);
  }
}

void Neoworm::Activate()
{
  if (IsTriggered())
    return;

  m_IsTriggered = true;
  m_IsActivated = true;

  m_Velocity.SetY(-444.f * Physics::GRAVITY);
  SetWalkState(NeowormWalkState::Left);

  m_Width = NEOWORM_WIDTH;
  m_Height = NEOWORM_HEIGHT;
}
