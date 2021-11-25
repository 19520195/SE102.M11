#include "SophiaIII.hh"
#include "Engine/Renderer/Animation.hh"

SophiaIII::SophiaIII()
{
  m_BarrelAID = 0;
  m_HammerAID = 0;
  m_GripAID   = 0;
  m_WheelAID  = 0;
}

void SophiaIII::SetState(int state)
{
  Character::SetState(state);
  
  switch (state)
  {
  case SOPHIAIII_IDLE_LEFT:
  case SOPHIAIII_IDLE_RIGHT:
    m_SpeedX = 0;
    break;

  case SOPHIAIII_WALK_LEFT:
    m_SpeedX = -0.001f;
    break;

  case SOPHIAIII_WALK_RIGHT:
    m_SpeedX = 0.001f;
    break;
  }
}

void SophiaIII::SetAnimation(size_t barrel, size_t hammer, size_t grip, size_t wheel)
{
  m_BarrelAID = barrel;
  m_HammerAID = hammer;
  m_GripAID   = grip;
  m_WheelAID  = wheel;
}

void SophiaIII::Render()
{
  Vector2D barrel;
  Vector2D hammer;
  Vector2D grip;  
  Vector2D lwheel;
  Vector2D rwheel;

  switch (m_State)
  {
  case SOPHIAIII_IDLE_LEFT:
  case SOPHIAIII_WALK_LEFT:
    barrel = (*this) + Vector2D(0, 0);
    hammer = (*this) + Vector2D(8, 0);
    grip   = (*this) + Vector2D(8, 8);
    lwheel = (*this) + Vector2D(0, 12);
    rwheel = (*this) + Vector2D(16, 12);
    break;

  case SOPHIAIII_IDLE_RIGHT:
  case SOPHIAIII_WALK_RIGHT:
    barrel = (*this) + Vector2D(16, 0); 
    hammer = (*this) + Vector2D(0, 0); 
    grip   = (*this) + Vector2D(8, 8);
    lwheel = (*this) + Vector2D(0, 12);
    rwheel = (*this) + Vector2D(16, 12);
    break;
  }

  AnimationBase::Get()->Get(m_BarrelAID)->Render(barrel.GetX(), barrel.GetY());
  AnimationBase::Get()->Get(m_HammerAID)->Render(hammer.GetX(), hammer.GetY());
  AnimationBase::Get()->Get(m_GripAID)->Render(grip.GetX(), grip.GetY());
  AnimationBase::Get()->Get(m_WheelAID)->Render(lwheel.GetX(), lwheel.GetY());
  AnimationBase::Get()->Get(m_WheelAID)->Render(rwheel.GetX(), rwheel.GetY());
}
