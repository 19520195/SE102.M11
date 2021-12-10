#pragma once
#include "Enemy.hh"

class Stuka : public Enemy
{
public:
  Stuka();
  void Render(TimeStep elapsed);
};
