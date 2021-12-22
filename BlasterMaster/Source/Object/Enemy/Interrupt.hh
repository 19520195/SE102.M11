#pragma once
#include "Enemy.hh"

constexpr float INTERRUPT_WIDTH  = 22;
constexpr float INTERRUPT_HEIGHT = 18;

constexpr float INTERRUPT_TRIGGER_WIDTH  = 16.f;
constexpr float INTERRUPT_TRIGGER_HEIGHT = 78.f;

class Interrupt : public Enemy
{
public:
  Interrupt();
  Trigger* CreateTrigger();

  void Activate();

  void Render(TimeStep elapsed);

private:
  uint32_t m_SpriteID;
};
