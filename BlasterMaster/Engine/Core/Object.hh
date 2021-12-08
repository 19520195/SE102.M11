#pragma once

#include "Engine/Core/TimeStep.hh"
#include "Engine/Math/Math.hh"
#include "Engine/Renderer/Renderable.hh"

class Object : public Movable
{
public:
  Object();
  ~Object() = default;

  void SetSpeed(float speedX, float speedY);
  void SetState(int state);

  int GetState();

  virtual void Update(TimeStep elapsed);
  virtual void Update(TimeStep elapsed, std::vector<Object*> objects);
  virtual void Render(TimeStep elapsed);

protected:
  // float m_SpeedX;
  // float m_SpeedY;
  int m_State;
};

class RenderableObject : public Object, public Renderable
{
public:
  virtual void Render(TimeStep elapsed) = 0;
};

class SpriteObject : public RenderableObject
{
public:
  void Render(float X, float Y, TimeStep elapsed);
  void Render(TimeStep elapsed);
};

class AnimationObject : public RenderableObject
{
public:
  void Render(float X, float Y, TimeStep elapsed);
  void Render(TimeStep elapsed);
};
