#pragma once
#include "Engine/Core/Object.hh"

class Portal : public Object
{
public:
  virtual void Activate() const = 0;
};

#include "ScenePortal.hh"
