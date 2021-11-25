#pragma once

#include "Character.hh"

enum SophiaIIIState
{
  SOPHIAIII_IDLE_LEFT,
  SOPHIAIII_IDLE_RIGHT,

  SOPHIAIII_WALK_LEFT,
  SOPHIAIII_WALK_RIGHT,
};

class SophiaIII : public Character
{
public:
  SophiaIII();

  void SetState(int state);
  
  void SetAnimation(size_t barrel, size_t hammer, size_t grip, size_t wheel);

  void Render();

private:
  size_t m_BarrelAID;
  size_t m_HammerAID;
  size_t m_GripAID;
  size_t m_WheelAID;
};
