#pragma once
#include "Engine/Core/Base.hh"
#include "Engine/Core/Object.hh"

class Object;

class Collider2D
{
public:
  Collider2D() = delete;
  Collider2D(Object* refer);

  Box2F GetBoundingBox() const;

private:
  // Vector2F    m_Scale;
  Object* m_Refer;
};
