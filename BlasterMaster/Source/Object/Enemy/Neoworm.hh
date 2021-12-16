#pragma once
#include "Enemy.hh"

constexpr float NEOWORM_WIDTH       = 0.f;
constexpr float NEOWORM_HEIGHT      = 0.f;
constexpr float NEOWORMFALL_WIDTH   = 9.f;
constexpr float NEOWORMFALL_HEIGHT  = 9.f;

class Neoworm : public Enemy
{
public:
  Neoworm(Vector2F p);
  void Render(TimeStep elapsed);

private:
  uint32_t m_SpriteID;
};

