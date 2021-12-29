#pragma once
#include "Collider2D.hh"
#include "Engine/Math/Vector.hh"

class Collider2D;
class Collision2D
{
public:
  TimeStep GetTime() const;
  Vector2F GetNormal() const;
  Ref<Collider2D> GetCollider() const;

  static bool AABB(const Box2F& shl, const Box2F& shr);
  static Ref<Collision2D> SweptAABB(const Ref<Collider2D>& shl, const Ref<Collider2D>& shr);
  friend bool operator<(const Collision2D& shl, const Collision2D& shr);

protected:
  TimeStep        m_Time;
  Vector2F        m_Normal;
  Ref<Collider2D> m_Collider;
};
