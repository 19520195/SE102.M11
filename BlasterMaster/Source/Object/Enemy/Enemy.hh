#pragma once
#include "Engine/Core/Object.hh"
#include "Object/State.hh"
#include "Resources/Resources.hh"

class Enemy;
class Trigger;

class Enemy : public Object 
{
public:
  Enemy();
  bool IsActivated() const;

  virtual void SetStartPoint(const Vector2F& point);
  virtual Trigger* CreateTrigger();

  virtual void Activate();
  virtual void Deactivate();

  static Enemy* Create(const std::string& name);

protected:
  Vector2F m_StartPoint;
  bool     m_IsActived;
};

class Trigger : public Object
{
public:
  Trigger() = delete;
  Trigger(Enemy* refer);

  void Start();

private:
  Enemy* m_Refer;
};

#include "Interrupt.hh"
#include "Ballbot.hh"
#include "Stuka.hh"
#include "Eyelet.hh"
#include "BallCarry.hh"
