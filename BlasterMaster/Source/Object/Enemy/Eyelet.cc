#include "Eyelet.hh"

Eyelet::Eyelet()
{
  // 
}

void Eyelet::Render(TimeStep elapsed)
{
  AnimationBase::GetInstance()
    ->Get(ANMID_EYELET)
    ->Render(m_X, m_Y, elapsed);
}
