#include "Eyelet.hh"

Eyelet::Eyelet()
{
  //
}

void Eyelet::SetStartPoint(const Vector2F& point)
{
  m_StartPoint.SetX(point.GetX());
  m_StartPoint.SetY(point.GetY() - EYELET_RANGE);
}

void Eyelet::Update(TimeStep elasped)
{
  m_X -= elasped * 0.1f;
  float deltaX = m_X - m_StartPoint.GetX() + acos(1.f) / 2 * EYELET_RANGE;
  m_Y = m_StartPoint.GetY() + EYELET_RANGE * std::sin(deltaX / EYELET_RANGE);
}

void Eyelet::Render(TimeStep elapsed)
{
  AnimationBase::GetInstance()
    ->Get(ANMID_EYELET_RIGHT)
    ->Render(m_X, m_Y, elapsed);
}
