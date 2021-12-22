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
  m_IsActived = true;
  auto player = static_cast<PlayScene*>(Game::GetInstance()->GetScene())->GetPlayer();
  m_SpeedX = (player->GetX() - m_X > 0 ? BALLBOT_WALKSPEED : -BALLBOT_WALKSPEED);
  m_SpeedY = BALLBOT_JUMPSPEED;
}

void Ballbot::Update(TimeStep elapsed)
{
  if (m_IsActived)
  {
    float beginVelocityY = m_SpeedY;
    float endVelocityY = m_SpeedY + BALLBOT_GRAVITY * elapsed;
    m_SpeedY = (beginVelocityY + endVelocityY) / 2;
  
    m_X += m_SpeedX * elapsed;
    m_Y += m_SpeedY * elapsed;
  }
}

void Ballbot::Render(TimeStep elapsed)
{
  AnimationBase::GetInstance()
    ->Get(ANMID_BALLBOT)
    ->Render(m_X, m_Y, elapsed);
}
