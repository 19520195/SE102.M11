#pragma once

#include "Engine/Core/Object.hh"
#include "Resources/Resources.hh"

class Enemy : public Object 
{
public:
  virtual void SetStartPoint(const Vector2F& point);
  virtual void SetActiveZone(const Box2F& activeZone);

  static Enemy* Create(const std::string& name);

protected:
  Vector2F m_StartPoint;
  Box2F    m_ActiveZone;
};

#include "Interrupt.hh"
#include "Ballbot.hh"
#include "Stuka.hh"
#include "Eyelet.hh"
#include "BallCarry.hh"
