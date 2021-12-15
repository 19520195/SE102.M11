#pragma once

#include "Engine/Core/Object.hh"
#include "Resources/Resources.hh"

class Enemy : public Object 
{
public:
  virtual void SetStartPoint(const Vector2F& point);

  static Enemy* Create(const std::string& name);

protected:
  Vector2F m_StartPoint;
};

#include "Interrupt.hh"
#include "Ballbot.hh"
#include "Stuka.hh"
#include "Eyelet.hh"
#include "BallCarry.hh"
