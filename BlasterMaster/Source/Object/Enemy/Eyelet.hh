#pragma once
#include "Enemy.hh"

constexpr float EYELET_RANGE = 24.0f;
constexpr float EYELET_SPEED = 0.08f;

class Eyelet : public Enemy
{
public:
  Eyelet();
  
  void SetStartPoint(const Vector2D& point);
 
  void Update(TimeStep elasped);
  void Render(TimeStep elapsed);
};
