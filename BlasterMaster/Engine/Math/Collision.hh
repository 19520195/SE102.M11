#pragma once

#include "Engine/Debug/Debug.hh"
#include "Engine/Core/TimeStep.hh"
#include "Box.hh"
#include <cstdint>

class Movable : public Box2F
{
public:
  Movable(float speedX, float speedY, float X, float Y, float width, float height);
  Movable(Vector2F speed = Vector2F(0, 0), Box2F bounding = Box2F(0, 0, 0, 0));

  float GetSpeedX() const;
  float GetSpeedY() const;
  Vector2F GetVelocity() const;
  Vector2F GetAcceleration() const;

  void SetVelocity(const Vector2F& velocity);

  Movable GetMove(float delta) const;
  void Move(float delta);

protected:
  Vector2F m_Velocity;
  Vector2F m_Acceleration;
};

class Collider
{
  friend class Collision;

public:
  enum class Direction : uint8_t
  {
    None,
    Top,
    Left,
    Right,
    Bottom,
  };

public:
  Vector2F GetDeltaTime() const;
  Direction GetDirection() const;

  float GetCollisionTime() const;

protected:
  Vector2F  m_DeltaTime;
  Direction m_Direction;
};

class Collision
{
public:
  static bool IsCollideX(const Box2F& object, const Box2F& other);
  static bool IsCollideY(const Box2F& object, const Box2F& other);

  static bool AABB(const Box2F& object, const Box2F& other);
  static float SweptAABB(const Movable& object, const Movable& other);
  static Collider SweptAABBx(const Movable& object, const Box2F& other);
};
