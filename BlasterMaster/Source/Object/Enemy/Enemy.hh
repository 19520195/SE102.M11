#pragma once

#include "Engine/Core/Object.hh"
#include "Resources/Resources.hh"

class Enemy : public Object 
{
public:
  Box2F GetActiveZone() const;
  bool  IsActivated() const;

  virtual void SetStartPoint(const Vector2F& point);
  virtual void SetActiveZone(const Box2F& activeZone);

  virtual void Activate();
  virtual void Deactivate();

  static Enemy* Create(const std::string& name);

protected:
  Vector2F m_StartPoint;
  bool     m_IsActived;
  Box2F    m_ActiveZone;
};

#include "Interrupt.hh"
#include "Ballbot.hh"
#include "Stuka.hh"
#include "Eyelet.hh"
#include "BallCarry.hh"
#include "Trigger.hh"
