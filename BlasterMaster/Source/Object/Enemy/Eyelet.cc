#include "Eyelet.hh"

constexpr float EYELET_TRIGGER_WITDH  = 16.f;
constexpr float EYELET_TRIGGER_HEIGHT = SCREEN_HEIGHT;

Eyelet::Eyelet()
{
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
    m_SpeedX = -EYELET_SPEED;
    m_RenderID = ANMID_EYELET_RIGHT;
  }
  else
  {
    m_SpeedX = EYELET_SPEED;
    m_RenderID = ANMID_EYELET_LEFT;
  }
}

void Eyelet::SetStartPoint(const Vector2F& point)
{
  m_StartPoint.SetX(point.GetX());
  m_StartPoint.SetY(point.GetY() - EYELET_RANGE);
}

void Eyelet::Update(TimeStep elasped)
{
  if (m_IsActived)
  {
    m_X += elasped * GetSpeedX();
    float deltaX = m_X - m_StartPoint.GetX() + acos(1.f) / 2 * EYELET_RANGE;
    m_Y = m_StartPoint.GetY() + EYELET_RANGE * std::sin(deltaX / EYELET_RANGE);
  }
}

void Eyelet::Render(TimeStep elapsed)
{
  if (m_IsActived)
    AnimationBase::GetInstance()
      ->Get(m_RenderID)
      ->Render(m_X, m_Y, elapsed);
}
