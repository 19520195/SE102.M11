#pragma once
#include "Vector.hh"

class Physic
{
public:
  static Vector2F CalculateDisplacement(const float& elapsed, const Vector2F& velocity, const Vector2F& acceleration);
};
