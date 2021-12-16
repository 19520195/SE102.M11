#include "Eyelet.hh"

Eyelet::Eyelet()
{
  m_IsActived = false;
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
    m_X -= elasped * 0.1f;
    float deltaX = m_X - m_StartPoint.GetX() + acos(1.f) / 2 * EYELET_RANGE;
    m_Y = m_StartPoint.GetY() + EYELET_RANGE * std::sin(deltaX / EYELET_RANGE);
  }
}

void Eyelet::Render(TimeStep elapsed)
{
  if (m_IsActived)
    AnimationBase::GetInstance()
      ->Get(ANMID_EYELET_RIGHT)
      ->Render(m_X, m_Y, elapsed);
}
