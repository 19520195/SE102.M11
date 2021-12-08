#pragma once

#include "Engine/Core/Object.hh"
#include "Engine/Renderer/Renderable.hh"

class Bullet : public Object
{
public:
  virtual void Update(TimeStep elapsed);
  virtual void Update(TimeStep elapsed, std::vector<Object*> objects);
  virtual void Render(TimeStep elapsed);
};

#include "SophiaIIIBullet.hh"
