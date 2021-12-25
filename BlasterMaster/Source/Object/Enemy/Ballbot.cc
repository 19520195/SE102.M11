#include "Ballbot.hh"
#include "Engine/Core/Game.hh"
#include "Scene/PlayScene.hh"

constexpr float BALLBOT_TRIGGER_WITDH  =  48.f;
constexpr float BALLBOT_TRIGGER_HEIGHT = 144.f;
constexpr float BALLBOT_WALKSPEED =  0.025f;
constexpr float BALLBOT_JUMPSPEED = -0.325f;
constexpr float BALLBOT_GRAVITY   =  0.001f;

Ballbot::Ballbot()
{
  // 
}

Trigger* Ballbot::CreateTrigger()
{
  Trigger* trigger = new Trigger(this);
  trigger->SetLocation(m_X, m_Y);
  trigger->SetX(m_X + (m_Width - BALLBOT_TRIGGER_WITDH) / 2);
  trigger->SetY(m_Y + (m_Height - BALLBOT_TRIGGER_HEIGHT));
  trigger->SetSize(BALLBOT_TRIGGER_WITDH, BALLBOT_TRIGGER_HEIGHT);
  return trigger;
}

void Ballbot::Activate()
{
  m_IsTriggered = true;
  auto player = std::static_pointer_cast<PlayScene>(Game::GetInstance()->GetScene())->GetPlayer();
  m_SpeedX = (player->GetX() - m_X > 0 ? BALLBOT_WALKSPEED : -BALLBOT_WALKSPEED);
  m_SpeedY = BALLBOT_JUMPSPEED;
}

void Ballbot::Update(TimeStep elapsed)
{
  if (m_IsTriggered)
  {
    float beginVelocityY = m_SpeedY;
    float endVelocityY = m_SpeedY + BALLBOT_GRAVITY * elapsed;
    m_SpeedY = (beginVelocityY + endVelocityY) / 2;
    
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

    Vector2F delta(m_SpeedX, m_SpeedY);
    delta = delta * deltaTime;
    
    *dynamic_cast<Vector2F*>(this) = (*this) + delta;

    if (delta.GetY() == 0)
    {
      m_SpeedY = 0;
      if (ceiled)
      {
        m_SpeedX = 0;
        this->ResetTrigger();
        currentScene->AddObject(CreateTrigger());
      }
    }
  }
}

void Ballbot::Render(TimeStep elapsed)
{
  AnimationBase::GetInstance()
    ->Get(ANMID_BALLBOT)
    ->Render(m_X, m_Y, elapsed);
}
