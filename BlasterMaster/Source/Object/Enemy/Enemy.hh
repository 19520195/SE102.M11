#pragma once

#include "Engine/Core/Object.hh"
#include "Resources/Resources.hh"

class Enemy : public Object 
{
public:
  Enemy();
  bool IsActivated() const;

  virtual void SetStartPoint(const Vector2F& point);

  virtual void Activate();
  virtual void Deactivate();

  static Enemy* Create(const std::string& name);

protected:
  Vector2F m_StartPoint;
  bool     m_IsActived;
};

#include "Interrupt.hh"
#include "Ballbot.hh"
#include "Stuka.hh"
#include "Eyelet.hh"
#include "BallCarry.hh"
#include "Trigger.hh"
