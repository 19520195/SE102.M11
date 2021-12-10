#pragma once
#include "Enemy.hh"

class Eyelet : public Enemy
{
public:
  Eyelet();
  void Render(TimeStep elapsed);
};
