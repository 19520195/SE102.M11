#pragma once
#include "Engine/Core/Base.hh"
#include "Engine/Core/TimeStep.hh"
#include "Engine/Math/Math.hh"
#include "Engine/Renderer/IRender2D.hh"
#include "Engine/Renderer/Renderable.hh"
#include "Engine/Physic/Collider2D.hh"

class Collider2D;

class Object : public Movable
{
public:
  Object();
  ~Object() = default;

  void SetSpeed(float speedX, float speedY);
  virtual void SetState(int state);
  virtual void Die();

  int GetState();
  Ref<Collider2D> GetCollider() const;
  virtual bool IsDied() const;

  void SetSprite(const std::string& name);
  void SetAnimation(const std::string& name);

  virtual void Update(TimeStep elapsed);
  virtual void Update(TimeStep elapsed, std::vector<Object*> objects);
  virtual void Render(TimeStep elapsed);

protected:
  int  m_State;
  bool m_Died;

  Ref<IRender2D>  m_Render;
  Ref<Collider2D> m_Collider;
};

// class RenderableObject : public Object, public Renderable
// {
// public:
//   virtual void Render(TimeStep elapsed) = 0;
// };
// 
// class SpriteObject : public RenderableObject
// {
// public:
//   void Render(float X, float Y, TimeStep elapsed);
//   void Render(TimeStep elapsed);
// };
// 
// class AnimationObject : public RenderableObject
// {
// public:
//   void Render(float X, float Y, TimeStep elapsed);
//   void Render(TimeStep elapsed);
// };
