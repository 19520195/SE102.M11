#pragma once
#include "Engine/Core/Object.hh"

class Bullet : public Object
{
public:
  virtual void Update(TimeStep elapsed);
};
