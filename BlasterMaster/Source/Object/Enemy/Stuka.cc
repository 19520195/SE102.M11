#include "Stuka.hh"
#include "Engine/Core/Game.hh"
#include "Scene/PlayScene.hh"

Stuka::Stuka() : m_Trail(0), m_CustomState(StukaState::Left)
{
  m_Render = AnimationBase::GetInstance()->Get("Stuka");
}

void Stuka::SetTrail(float trail)
{
  m_Trail = trail;
}

void Stuka::SetState(const StukaState& state)
{
  m_CustomState = state;
}

void Stuka::Update(TimeStep elapsed)
{
  auto player = std::static_pointer_cast<PlayScene>(Game::GetInstance()->GetScene())->GetPlayer();
  
  Vector2F direct = (player->GetLocation()) - (this->GetLocation());
  if (direct.Abs() > STUKA_RANGE)
  {
    // Folow the trail if can not see player
    direct = Vector2F(m_X, m_Trail) - this->GetLocation();
    direct.SetX(m_CustomState == StukaState::Left ? -1.f : 1.f);
  }

  // Set velocity to reach target (player/trail)
  this->SetVelocity(STUKA_SPEED * direct.GetUnit());

  // Update
  Enemy::Update(elapsed);
}

