#pragma once
#include "Engine/Core/Object.hh"
#include "Object/State.hh"

class Enemy;
class Trigger;

class Enemy : public Object 
{
public:
  Enemy();
  bool IsActivated() const;
  bool IsTriggered() const;

  virtual Trigger* CreateTrigger();

  virtual void Activate();
  virtual void ResetTrigger();

  static Ref<Enemy> Create(const std::string& name);

protected:
  bool m_IsActivated;
  bool m_IsTriggered;
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
