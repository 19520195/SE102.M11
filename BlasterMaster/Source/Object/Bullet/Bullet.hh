#pragma once
#include "Engine/Core/Object.hh"

class Bullet : public Object
{
public:
  Bullet();
  virtual void Update(TimeStep elapsed);

protected:
  TimeStep m_Arrival;
};
