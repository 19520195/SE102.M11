#include "BallCarry.hh"

BallCarry::BallCarry()
{
  // 
}

void BallCarry::Render(TimeStep elapsed)
{
  AnimationBase::GetInstance()
    ->Get(ANMID_BALL_CARRY)
    ->Render(m_X, m_Y, elapsed);
}
