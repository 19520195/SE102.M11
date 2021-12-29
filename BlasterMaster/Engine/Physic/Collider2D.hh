#pragma once
#include "Material.hh"
#include "Physics.hh"
#include "Collision2D.hh"

class Object;
class Collision2D;

class Collider2D
{
public:
  Collider2D() = delete;
  Collider2D(Object* refer);

  Object* GetRefer() const;
  Ref<Material> GetMaterial() const;
  Vector2F GetDisplacement() const;

  void SetMaterial(Ref<Material> material);
  void SetDisplacement(const Vector2F& displacement);
  void CalculateDisplacement(const TimeStep& elapsed);

  void UpdateRefer();
  void Update(Ref<Collision2D> collision);

private:
  Object*       m_Refer;
  Ref<Material> m_Material;
  Vector2F      m_Displacement;
  Vector2F      m_Velocity;
};
