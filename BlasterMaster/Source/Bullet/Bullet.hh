#pragma once

#include "Engine/Core/Object.hh"

class Bullet : public Object
{
public:
  virtual void Update(TimeStep elapsed)
  {
    m_X += m_SpeedX * elapsed;
    m_Y += m_SpeedY * elapsed;
  }
};

#include "SophiaIIIBullet.hh"
