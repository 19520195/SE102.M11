#pragma once

#include "Renderer.hh"

class Renderable
{
public:
  Renderable();

  void SetID(size_t ID);

  virtual void Render(float X, float Y, TimeStep elapsed) = 0; 

protected:
  size_t m_ID;
};
