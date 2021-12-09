#pragma once

#include "Engine/Core/Object.hh"

class Interrupt;

class Enemy : public Object 
{
public:
  static Enemy* Create(const std::string& name);
};

#include "Interrupt.hh"
