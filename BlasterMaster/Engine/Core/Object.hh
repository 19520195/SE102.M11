#pragma once
#include "Base.hh"
#include "TimeStep.hh"
#include "Behavior.hh"
#include "Engine/Renderer/Renderer.hh"
#include "Engine/Math/Math.hh"
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
  Behavior GetBehavior() const;
  Ref<Collider2D> GetCollider() const;
  virtual bool IsDied() const;

  virtual void SetBehavior(const Behavior& behavior);
  void SetSprite(const std::string& name);
  void SetAnimation(const std::string& name);

  virtual void Update(TimeStep elapsed);
  virtual void Update(TimeStep elapsed, std::vector<Ref<Object>> objects);
  virtual void Render(TimeStep elapsed);

protected:
  int  m_State;
  bool m_Died;

  Behavior        m_Behavior;
  Ref<IRender2D>  m_Render;
  Ref<Collider2D> m_Collider;
};

