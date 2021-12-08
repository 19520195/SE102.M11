#pragma once

#include "Engine/Core/Object.hh"
#include "Engine/Renderer/Renderable.hh"

class Bullet : public Object
{
public:
  virtual void Update(TimeStep elapsed);
};

#include "SophiaIIIBullet.hh"
