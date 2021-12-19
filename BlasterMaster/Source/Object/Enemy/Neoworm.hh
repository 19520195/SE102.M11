#pragma once
#include "Enemy.hh"
#include "Object/Brick.hh"

constexpr float NEOWORM_WIDTH       = 18.f;
constexpr float NEOWORM_HEIGHT      = 10.f;
constexpr float NEOWORMFALL_WIDTH   =  9.f;
constexpr float NEOWORMFALL_HEIGHT  =  9.f;

constexpr float NEOWORMFALL_GRAVITY   = 0.001f;
constexpr float NEOWORMFALL_JUMPSPEED = 0.2f;


class Neoworm : public Enemy
{
public:
  Neoworm(Vector2F p);

  void CollideWithBrick(Brick* brick, TimeStep elapsed, Vector2F& deltaTime);

  void Activate();
  
  void Update(TimeStep elapsed);
  void Render(TimeStep elapsed);

private:
  uint32_t m_SpriteID;
};

