#include "Ballbot.hh"
#include "Engine/Core/Game.hh"
#include "Scene/PlayScene.hh"

Ballbot::Ballbot()
{
}

// Trigger* Ballbot::CreateTrigger()
// {
//   Trigger* trigger = new Trigger(this);
//   trigger->SetLocation(m_X, m_Y);
//   trigger->SetX(m_X + (m_Width - BALLBOT_TRIGGER_WITDH) / 2);
//   trigger->SetY(m_Y + (m_Height - BALLBOT_TRIGGER_HEIGHT));
//   trigger->SetSize(BALLBOT_TRIGGER_WITDH, BALLBOT_TRIGGER_HEIGHT);
//   return trigger;
// }

void Ballbot::Activate()
{
  m_IsTriggered = true;
  auto player = std::static_pointer_cast<PlayScene>(Game::GetInstance()->GetScene())->GetPlayer();
  m_Velocity.SetX((player->GetX() - m_X > 0 ? BALLBOT_WALKSPEED : -BALLBOT_WALKSPEED));
  m_Velocity.SetY(BALLBOT_JUMPSPEED);
}

void Ballbot::Update(TimeStep elapsed)
{
  if (m_IsTriggered)
  {
    float beginVelocityY = m_Velocity.GetY();
    float endVelocityY = m_Velocity.GetY() + BALLBOT_GRAVITY * elapsed;
    m_Velocity.SetY((beginVelocityY + endVelocityY) / 2);
    
    Vector2F deltaTime = static_cast<float>(elapsed);

    bool ceiled = false;
    auto currentScene = std::static_pointer_cast<PlayScene>(Game::GetInstance()->GetScene());
    auto objects = currentScene->GetObjects();
    for (const auto& object : objects)
    {
      if (dynamic_cast<Brick*>(object))
      {
        Collider collider = Collision::SweptAABBx(*this, *object);
        if (IN_RANGE(collider.GetCollisionTime(), 0, static_cast<float>(elapsed)))
        {
          ceiled |= (collider.GetDirection() == Collider::Direction::Top);
          deltaTime = Vector2F::Min(deltaTime, collider.GetDeltaTime());
        }
      }
    }
    
    deltaTime = Vector2F::Max(deltaTime, 0);

    Vector2F delta(m_Velocity.GetX(), m_Velocity.GetY());
    delta = delta * deltaTime;
    
    *dynamic_cast<Vector2F*>(this) = (*this) + delta;

    if (delta.GetY() == 0)
    {
      m_Velocity.SetY(0);
      if (ceiled)
      {
        m_Velocity.SetX(0);
        this->ResetTrigger();
      }
    }
  }
  else
  {
    auto player = std::static_pointer_cast<PlayScene>(
      Game::GetInstance()->GetScene())->GetPlayer();
    Vector2F direct = this->GetCenter() - player->GetCenter();
    if (IN_RANGE(direct.GetX(), -BALLBOT_TRIGGER_WITDH, BALLBOT_TRIGGER_WITDH) &&
      IN_RANGE(direct.GetY(), 0, BALLBOT_TRIGGER_HEIGHT))
    {
      DEBUG_MSG(L"X = %.2f, Y = %.2f\n", direct.GetX(), direct.GetY());
      this->Activate();
    }
  }
}

void Ballbot::Render(TimeStep elapsed)
{
  AnimationBase::GetInstance()
    ->Get(ANMID_BALLBOT)
    ->Render(m_X, m_Y, elapsed);
}
