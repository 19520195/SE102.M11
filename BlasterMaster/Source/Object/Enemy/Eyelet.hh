#pragma once
#include "Object/Object.hh"

class Eyelet : public Enemy
{
public:
  Eyelet();
  void Render(TimeStep elapsed);
};
