#pragma once
#include "Enemy.hh"
#include "Object/Brick.hh"

constexpr float NEOWORM_WIDTH       = 18.f;
constexpr float NEOWORM_HEIGHT      = 10.f;
constexpr float NEOWORMFALL_WIDTH   =  9.f;
constexpr float NEOWORMFALL_HEIGHT  =  9.f;

constexpr float NEOWORMFALL_SPEED     = 0.07f;
constexpr float NEOWORMFALL_GRAVITY   = 0.001f;
constexpr float NEOWORMFALL_JUMPSPEED = 0.2f;

enum class NeowormWalkState : uint8_t
{
  Left,
  Right, 
  Chase
};

class Neoworm : public Enemy
{
public:
  Neoworm(Vector2F p);
  void SetWalkState(NeowormWalkState ws);

  void OnCollide(const Ref<Collision2D>& collision) override;

  void Activate();

private:
  NeowormWalkState m_WalkState;
};
