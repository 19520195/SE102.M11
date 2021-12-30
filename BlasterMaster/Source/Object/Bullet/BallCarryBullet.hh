#pragma once
#include "Bullet.hh"

class BallCarryBullet : public Bullet
{
public:
  BallCarryBullet();
  bool IsDied() const override;
  void OnCollide(const Ref<Collision2D>& collison) override;
};
