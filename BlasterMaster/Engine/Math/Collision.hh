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
  Movable GetMove(float delta) const;

  void Move(float delta);

protected:
  float m_SpeedX;
  float m_SpeedY;
};

class Collision
{
public:
  enum class Direction : uint8_t
  {
    DIRECT_NONE,
    DIRECT_EAST,
    DIRECT_WEST,
    DIRECT_SOUTH,
    DIRECT_NORTH,
  };

public:
  static bool IsCollideX(const Box2F& object, const Box2F& other);
  static bool IsCollideY(const Box2F& object, const Box2F& other);

  static bool AABB(const Box2F& object, const Box2F& other);
  static float SweptAABB(const Movable& object, const Movable& other);
};
