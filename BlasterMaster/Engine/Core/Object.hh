#pragma once

#include "Engine/Core/TimeStep.hh"
#include "Engine/Math/Math.hh"
#include "Engine/Renderer/Renderable.hh"

class Object : public Vector2D
{
public:
  Object();
  ~Object() = default;

  void SetPos(float X, float Y);
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
  virtual void Render() = 0; 
};

class SpriteObject : public RenderableObject
{
public:
  void Render(float X, float Y)
  {
    SpriteBase::GetInstance()->Get(m_ID)->Render(X, Y); 
  }

  void Render()
  {
    Render(m_X, m_Y); 
  }
};

class AnimationObject : public RenderableObject
{
public:
  void Render(float X, float Y)
  {
    AnimationBase::GetInstance()->Get(m_ID)->Render(X, Y);
  }

  void Render()
  {
    Render(m_X, m_Y);
  }
};
