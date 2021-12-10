#pragma once

#include "Engine/Core/Object.hh"
#include "Engine/Renderer/Renderable.hh"
#include "Resources/Resources.hh"

class Bullet : public Object
{
public:
  virtual void Update(TimeStep elapsed);
};
