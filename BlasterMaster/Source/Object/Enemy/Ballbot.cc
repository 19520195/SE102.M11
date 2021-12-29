#include "Ballbot.hh"
#include "Engine/Core/Game.hh"
#include "Scene/PlayScene.hh"

Ballbot::Ballbot()
{
  m_Acceleration = Vector2F(0.f, -Physics::GRAVITY);
  SetAnimation("Ballbot");
}

void Ballbot::OnCollide(const Ref<Collision2D>& collision)
{
  auto refer = collision->GetCollider()->GetRefer();
  if (dynamic_cast<Brick*>(refer) && collision->GetNormal().GetY() < 0)
  {
    m_Velocity.SetX(0);
    m_IsTriggered = false;
  }
}

void Ballbot::Activate()
{
  m_IsTriggered = true;
  auto player = std::static_pointer_cast<PlayScene>(Game::GetInstance()->GetScene())->GetPlayer();
  m_Velocity.SetX((player->GetX() - m_X > 0 ? BALLBOT_WALKSPEED : -BALLBOT_WALKSPEED));
  m_Velocity.SetY(Physics::GRAVITY * 666);
}

void Ballbot::Update()
{
  if (!m_IsTriggered)
  {
    auto player = std::static_pointer_cast<PlayScene>(
      Game::GetInstance()->GetScene())->GetPlayer();
    Vector2F direct = this->GetCenter() - player->GetCenter();
    if (IN_RANGE(direct.GetX(), -BALLBOT_TRIGGER_WITDH, BALLBOT_TRIGGER_WITDH) &&
      IN_RANGE(direct.GetY(), 0, BALLBOT_TRIGGER_HEIGHT))
    {
      this->Activate();
    }
  }
}
