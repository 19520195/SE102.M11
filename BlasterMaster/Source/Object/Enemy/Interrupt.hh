#pragma once
#include "Enemy.hh"

constexpr float INTERRUPT_WIDTH  = 22;
constexpr float INTERRUPT_HEIGHT = 18;

class Interrupt : public Enemy
{
public:
  Interrupt();
  void Render(TimeStep elapsed);

private:
};
