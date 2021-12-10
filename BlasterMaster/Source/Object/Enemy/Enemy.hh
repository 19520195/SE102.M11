#pragma once

#include "Engine/Core/Object.hh"
#include "Resources/Resources.hh"

class Enemy : public Object 
{
public:
  static Enemy* Create(const std::string& name);
};

#include "Interrupt.hh"
#include "Ballbot.hh"
#include "Stuka.hh"
#include "Eyelet.hh"
#include "BallCarry.hh"
