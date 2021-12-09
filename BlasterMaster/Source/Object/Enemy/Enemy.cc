#include "Enemy.hh"

Enemy* Enemy::Create(const std::string& name)
{
  if (name == "Interrupt") return new Interrupt();
  return nullptr;
}
