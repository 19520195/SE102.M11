#pragma once
#include "Enemy.hh"

constexpr float BALLBOT_TRIGGER_WITDH  =  24.f;
constexpr float BALLBOT_TRIGGER_HEIGHT = 112.f;

constexpr float BALLBOT_WALKSPEED =  0.025f;
constexpr float BALLBOT_JUMPSPEED = -0.325f;
constexpr float BALLBOT_GRAVITY   =  0.001f;

class Ballbot : public Enemy
{
public:
  Ballbot();
  void Activate();
  void Update(TimeStep elapsed);
  void Render(TimeStep elapsed);
};
