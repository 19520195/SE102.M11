#include "Stuka.hh"

Stuka::Stuka()
{
  // 
}

void Stuka::Render(TimeStep elapsed)
{
  AnimationBase::GetInstance()
    ->Get(ANMID_STUKA)
    ->Render(m_X, m_Y, elapsed);
}
