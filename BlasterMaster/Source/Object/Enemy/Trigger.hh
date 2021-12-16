#pragma once
#include "Enemy.hh"

class Trigger : public Object
{
public:
  Trigger() = delete;
  Trigger(Enemy* refer);
  
  void Start();

private:
  Enemy* m_Refer;
};

