#include "Eyelet.hh"
#include "Engine/Core/Game.hh"

constexpr float EYELET_TRIGGER_WITDH  = 16.f;
constexpr float EYELET_TRIGGER_HEIGHT = SCREEN_HEIGHT;

Eyelet::Eyelet()
{
  m_IsActivated = false;
  m_RenderID = 0;
}

Trigger* Eyelet::CreateTrigger()
{
  float X = m_X + (SD_IS_LEFT(m_State) ? -128 : 96);
  float Y = m_Y + (m_Height - EYELET_TRIGGER_HEIGHT) / 2;

  Trigger* trigger = new Trigger(this);
  trigger->SetLocation(X, Y);
  trigger->SetSize(EYELET_TRIGGER_WITDH, EYELET_TRIGGER_HEIGHT);
  return trigger;
}

void Eyelet::SetState(int state)
{
  Enemy::SetState(state);
  if (SD_IS_LEFT(m_State))
  {
    m_Velocity.SetX(-EYELET_SPEED);
    m_Render = AnimationBase::GetInstance()->Get("Eyelet-Left");
  }
  else
  {
    m_Velocity.SetX(EYELET_SPEED);
    m_Render = AnimationBase::GetInstance()->Get("Eyelet-Right");
  }
}

void Eyelet::SetLocation(float X, float Y)
{
  Box2F::SetLocation(X, Y);
  m_SpecialY = Y;
}

void Eyelet::Update(TimeStep elasped)
{
  if (m_IsTriggered)
  {
    m_X += elasped * GetSpeedX();
    float deltaX = static_cast<float>(Game::GetInstance()->GetLastFrameTime() * m_Velocity.GetX());
    m_Y = m_SpecialY + EYELET_RANGE * std::sin(deltaX / EYELET_RANGE);
  }
}

void Eyelet::Render(TimeStep elapsed)
{
  if (m_IsTriggered) Enemy::Render(elapsed);
}
