#pragma once
#include "Enemy.hh"

class Ballbot : public Enemy
{
public:
  Ballbot();
  Trigger* CreateTrigger();
  
  void Activate();
  void Update(TimeStep elapsed);
  void Render(TimeStep elapsed);
};
