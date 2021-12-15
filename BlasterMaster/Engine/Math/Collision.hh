#pragma once

#include "Engine/Debug/Debug.hh"
#include "Engine/Core/TimeStep.hh"
#include "Box.hh"

class Movable : public Box2F
{
public:
  Movable(float speedX, float speedY, float X, float Y, float width, float height);
  Movable(float speedX = 0, float speedY = 0, Box2F bounding = Box2F(0, 0, 0, 0));

  float GetSpeedX() const;
  float GetSpeedY() const;

  void Move(float delta);

protected:
  float m_SpeedX;
  float m_SpeedY;
};

class Collision
{
public:
  static bool IsCollideX(const Movable& object, const Movable& other);
  static bool IsCollideY(const Movable& object, const Movable& other);
  static bool AABB(const Movable& object, const Movable& other);
  static float SweptAABB(const Movable& object, const Movable& other);
};
