#include "Enemy.hh"

Enemy* Enemy::Create(const std::string& name)
{
  if (name == "Interrupt" ) return new Interrupt();
  if (name == "Ballbot"   ) return new Ballbot();
  if (name == "Stuka"     ) return new Stuka();
  if (name == "Eyelet"    ) return new Eyelet();
  if (name == "Ball-Carry") return new BallCarry();
  return nullptr;
}
