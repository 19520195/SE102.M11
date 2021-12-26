#include "BallCarry.hh"

BallCarry::BallCarry()
{
  // 
}

void BallCarry::Render(TimeStep elapsed)
{
  AnimationBase::GetInstance()
    ->Get("Ball-Carry")
    ->Render(m_X, m_Y, elapsed);
}
