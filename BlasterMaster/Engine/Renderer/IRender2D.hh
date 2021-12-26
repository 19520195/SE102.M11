#pragma once
#include "Engine/Core/TimeStep.hh"

class IRender2D
{
public:
  virtual void Render(float X, float Y, TimeStep elapsed) = 0;
};
