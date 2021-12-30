#pragma once
#include "Enemy.hh"

enum class DrapWalkState : uint8_t
{
  Left,
  Right,
};

class Drap : public Enemy
{
public:
  Drap();
  void SetWalkState(const DrapWalkState& ws);
  void OnCollide(const Ref<Collision2D>& collision) override;
  void Update() override;

private:
  DrapWalkState m_WalkState;
};
