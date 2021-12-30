#include "Drap.hh"
#include "Engine/Core/Game.hh"
#include "Scene/PlayScene.hh"

constexpr float DRAP_RANGE    = 16.f;
constexpr float DRAP_VELOCITY =  0.2f;

Drap::Drap()
{
  SetAnimation("Drap-Spin-Left");
}

void Drap::SetWalkState(const DrapWalkState& ws)
{
  switch (m_WalkState = ws)
  {
  case DrapWalkState::Left:
    m_Velocity.SetX(-DRAP_VELOCITY);
    SetAnimation("Drap-Spin-Left");
    break;

  case DrapWalkState::Right:
    m_Velocity.SetX(DRAP_VELOCITY);
    SetAnimation("Drap-Spin-Right");
    break;
  }
}

void Drap::OnCollide(const Ref<Collision2D>& collision)
{
  // Reset Trigger
  if (dynamic_cast<Brick*>(collision->GetCollider()->GetRefer()))
    m_IsTriggered = false;
}

void Drap::Update()
{
  if (IsTriggered()) return;
  auto scene = std::static_pointer_cast<PlayScene>(
    Game::GetInstance()->GetScene());
  auto player = scene->GetPlayer();

  Vector2F delta = player->GetLocation() - this->GetLocation();
  if (!IsInRange(delta.GetY(), -DRAP_RANGE, DRAP_RANGE)) return;

  DEBUG_MSG(L"Triggered Drap\n");
  m_IsTriggered = true;
  
  if (delta.GetX() < 0)
    SetWalkState(DrapWalkState::Left);
  else SetWalkState(DrapWalkState::Right);
}
