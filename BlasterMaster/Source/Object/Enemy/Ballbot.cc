#include "Ballbot.hh"

Ballbot::Ballbot()
{
  // 
}

void Ballbot::Render(TimeStep elapsed)
{
  AnimationBase::GetInstance()
    ->Get(ANMID_BALLBOT)
    ->Render(m_X, m_Y, elapsed);
}
