#pragma once
#include "Object/Object.hh"

class Ballbot : public Enemy
{
public:
  Ballbot();
  void Render(TimeStep elapsed);
};
