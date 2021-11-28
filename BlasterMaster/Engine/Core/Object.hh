#pragma once

#include "Engine/Core/TimeStep.hh"
#include "Engine/Math/Math.hh"
#include "Engine/Renderer/Renderable.hh"

class Object : public Vector2D
{
public:
  Object();
  ~Object() = default;

  void SetSpeed(float speedX, float speedY);
  void SetState(int state);

  int GetState();

  void Update(TimeStep step);

protected:
  float m_SpeedX;
  float m_SpeedY;

  int   m_State;
};

class RenderableObject : public Object, public Renderable
{
public:
  virtual void Render(TimeStep step) = 0; 
};

class SpriteObject : public RenderableObject
{
public:
  void Render(float X, float Y, TimeStep step)
  {
    SpriteBase::GetInstance()->Get(m_ID)->Render(X, Y); 
  }

  void Render(TimeStep step)
  {
    Render(m_X, m_Y, step); 
  }
};

class AnimationObject : public RenderableObject
{
public:
  void Render(float X, float Y, TimeStep step)
  {
    AnimationBase::GetInstance()->Get(m_ID)->Render(X, Y, step);
  }

  void Render(TimeStep step)
  {
    Render(m_X, m_Y, step);
  }
};
