#include "Physics.hh"
#include "Engine/Core/Game.hh"
#include <algorithm>

Vector2F Physics::CalculateDisplacement(const Move2F& entity, const float& elapsed)
{
  Vector2F u = entity.GetVelocity();
  Vector2F a = entity.GetAcceleration();
  
  Vector2F s = u * elapsed;
  // if (a != 0) s = s + .5f * elapsed * elapsed * a;
  return s;
}

List<Ref<Collision2D>>::iterator FindFirstCollision(List<Ref<Collision2D>>& collisions)
{
  auto iter = std::find_if(collisions.begin(), collisions.end(), [](const Ref<Collision2D>& value) {
    return value->GetCollider()->GetMaterial() != nullptr; });
  if (iter != collisions.end()) ++iter;
  return iter;
}

List<Ref<Collision2D>> Physics::FilterCollisions(List<Ref<Collision2D>>& collisions)
{
  List<Ref<Collision2D>> collisionXs;
  List<Ref<Collision2D>> collisionYs;

  for (const auto& collision : collisions)
    if (collision->GetNormal().GetX())
      collisionXs.emplace_back(collision);
    else collisionYs.emplace_back(collision);
  
  List<Ref<Collision2D>> filter;
  filter.insert(filter.end(), collisionXs.begin(), FindFirstCollision(collisionXs));
  filter.insert(filter.end(), collisionYs.begin(), FindFirstCollision(collisionYs));
  return filter;
}

List<Ref<Collision2D>> Physics::CalculateCollisions(Ref<Collider2D>& shl, List<Ref<Collider2D>>& colliders)
{
  List<Ref<Collision2D>> collisions;
  TimeStep elapsed = Game::GetInstance()->GetElapsedTime();
  for (auto& shr : colliders) if (shl != shr)
    if (Ref<Collision2D> collision = Collision2D::SweptAABB(shl, shr))
      collisions.emplace_back(collision);

  std::sort(collisions.begin(), collisions.end(),
    [](const Ref<Collision2D>& shl, const Ref<Collision2D>& shr) {
      return *shl < *shr; });
  return collisions;
}

void Physics::Calculate(List<Ref<Collider2D>>& colliders)
{
  TimeStep elapsed = Game::GetInstance()->GetElapsedTime();
  for (auto& shl : colliders)
  {
    shl->CalculateDisplacement(elapsed);

    auto collisions = CalculateCollisions(shl, colliders);
    collisions = FilterCollisions(collisions);
    
    for (auto& collision : collisions)
    {
      shl->GetRefer()->OnCollide(collision);
      if (collision->GetCollider()->GetMaterial())
        shl->Update(collision);
    }
  }
}
