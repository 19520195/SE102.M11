#include "Stuka.hh"
#include "Engine/Core/Game.hh"
#include "Scene/PlayScene.hh"

Stuka::Stuka() : m_Trail(0)
{
}

void Stuka::Update(TimeStep elapsed)
{
  auto player = std::static_pointer_cast<PlayScene>(Game::GetInstance()->GetScene())->GetPlayer();
  
  Vector2F direct = (player->GetLocation()) - (this->GetLocation());
  if (direct.Abs() > STUKA_RANGE)
  {
    // Folow the trail if can not see player
    // direct = Vector2F(m_X, m_Trail) - this->GetLocation();
    // direct.SetX(m_Velocity.GetX());
    // direct.SetY((STUKA_SPEED * direct.GetUnit()).GetY());
    direct = 0;
  }

  // Set velocity to reach target (player/trail)
  this->SetVelocity(STUKA_SPEED * direct.GetUnit());

  // Update
  Enemy::Update(elapsed);
}

void Stuka::Render(TimeStep elapsed)
{
  AnimationBase::GetInstance()
    ->Get("Stuka")
    ->Render(m_X, m_Y, elapsed);
}
