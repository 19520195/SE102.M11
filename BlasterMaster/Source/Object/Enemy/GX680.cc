#include "GX680.hh"
#include "Engine/Core/Game.hh"
#include "Scene/PlayScene.hh"

constexpr float GX680_WALK_SPEED = 0.04f;

GX680::GX680()
{
  SetWalkState(GX680WalkState::Left);
}

void GX680::SetWalkState(GX680WalkState ws)
{
  if (m_WalkState != ws)
  {
    switch (m_WalkState = ws)
    {
    case GX680WalkState::Left:
      SetAnimation("GX680-Walk-Left");
      break;

    case GX680WalkState::Right:
      SetAnimation("GX680-Walk-Right");
      break;
    }
  }
}

void GX680::Update()
{
  auto scene = std::static_pointer_cast<PlayScene>(
    Game::GetInstance()->GetScene());
  auto player = scene->GetPlayer();
  
  Vector2F velocity = player->GetLocation() - this->GetLocation();
  velocity = velocity / velocity.Abs();
  velocity = velocity * GX680_WALK_SPEED;
  m_Velocity = std::move(velocity);

  if (m_Velocity.GetX() < 0)
    SetWalkState(GX680WalkState::Left);
  else SetWalkState(GX680WalkState::Right);
}

GX680S::GX680S()
{
  SetAnimation("GX680S-Walk-Left");
}

void GX680S::SetWalkState(GX680WalkState ws)
{
  if (m_WalkState != ws)
  {
    switch (m_WalkState = ws)
    {
    case GX680WalkState::Left:
      SetAnimation("GX680S-Walk-Left");
      break;

    case GX680WalkState::Right:
      SetAnimation("GX680S-Walk-Right");
      break;
    }
  }
}
