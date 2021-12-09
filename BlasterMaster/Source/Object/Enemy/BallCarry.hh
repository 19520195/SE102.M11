#pragma once
#include "Object/Object.hh"

class BallCarry : public Enemy
{
public:
  BallCarry();
  void Render(TimeStep elapsed);
};
