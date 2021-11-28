#pragma once

#include "Renderer.hh"

class Renderable
{
public:
  Renderable(); 
  void SetID(size_t ID);

  virtual void Render(float X, float Y) = 0; 

protected:
  size_t m_ID;
};

class SpriteRender : public Renderable
{
public:
  virtual void Render(float X, float Y);
};

class AnimationRender : public Renderable
{
public:
  void Render(float X, float Y);
};
