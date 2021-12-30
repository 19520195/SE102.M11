#pragma once
#include "Enemy.hh"

enum class LazerGuardWalkState : uint8_t
{
  Left,
  Right,
};

class LazerGuard : public Enemy
{
public:
  LazerGuard();
  void SetWalkState(const LazerGuardWalkState& ws);
  void OnCollide(const Ref<Collision2D>& collision) override;
  void Update() override;

private:
  LazerGuardWalkState m_WalkState;
};
