#pragma once
#include "Enemy.hh"

enum class BallCarryWalkState
{
  Left,
  Right, 
  Shoot,
};

class BallCarry : public Enemy
{
public:
  BallCarry();
  void SetWalkState(BallCarryWalkState ws);
  void OnCollide(const Ref<Collision2D>& collison) override;
  void Update() override;

private:
  TimeStep           m_LastShootTime;
  BallCarryWalkState m_WalkState;
  BallCarryWalkState m_PrevWalkState;
};
