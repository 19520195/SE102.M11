#pragma once
#include "Engine/Core/Object.hh"
#include "Collision2D.hh"

namespace Physics
{
  using Move2F = Movable;

  Vector2F CalculateDisplacement(const Move2F& entity, const float& elapsed);

  List<Ref<Collision2D>> FilterCollisions(List<Ref<Collision2D>>& collisions);
  List<Ref<Collision2D>> CalculateCollisions(Ref<Collider2D>& shl, List<Ref<Collider2D>>& colliders);
  void Calculate(List<Ref<Collider2D>>& colliders);
};
