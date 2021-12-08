#pragma once
#include "Object/Object.hh"

constexpr float INTERRUPT_WIDTH  = 22;
constexpr float INTERRUPT_HEIGHT = 18;

class Interrupt : public Enemy
{
public:
  Interrupt();
  void Render(TimeStep elapsed);

private:
};
