#pragma once
#include "Enemy.hh"

class BallCarry : public Enemy
{
public:
  BallCarry();
  void Render(TimeStep elapsed);
};
