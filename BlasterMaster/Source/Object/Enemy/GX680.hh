#pragma once
#include "Enemy.hh"

enum class GX680WalkState : uint8_t
{
  Left,
  Right,
};

class GX680 : public Enemy
{
public:
  GX680();
  virtual void SetWalkState(GX680WalkState ws);
  void Update() override;

protected:
  GX680WalkState m_WalkState;
};

class GX680S : public GX680
{
public:
  GX680S();
  virtual void SetWalkState(GX680WalkState ws);
};
