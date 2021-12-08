#pragma once

#include "Engine/Core/Object.hh"

class Bullet : public Object
{
public:
  virtual void Update(TimeStep elapsed);
  virtual void Update(TimeStep elapsed, std::vector<Object*> objects);
};

#include "SophiaIIIBullet.hh"
