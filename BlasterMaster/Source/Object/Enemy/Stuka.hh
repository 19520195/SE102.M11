#pragma once
#include "Object/Object.hh"

class Stuka : public Enemy
{
public:
  Stuka();
  void Render(TimeStep elapsed);
};
