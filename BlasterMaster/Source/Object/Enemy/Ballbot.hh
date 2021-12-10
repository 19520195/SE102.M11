#pragma once
#include "Enemy.hh"

class Ballbot : public Enemy
{
public:
  Ballbot();
  void Render(TimeStep elapsed);
};
