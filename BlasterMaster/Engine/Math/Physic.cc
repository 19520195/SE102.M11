#include "Physic.hh"

Vector2F Physic::CalculateDisplacement(const float& elapsed, const Vector2F& velocity, const Vector2F& acceleration)
{
  // S = uT + ��a��T
  return (elapsed * velocity) + 0.5f * (acceleration * acceleration * elapsed);
}
