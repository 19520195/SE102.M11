#pragma once

#include "Engine/Debug/Debug.hh"
#include "Engine/Core/TimeStep.hh"
#include "Vector.hh"

class Box2F : public Vector2F
{
public:
  Box2F(float X = 0, float Y = 0, float width = 0, float height = 0); 

  float GetWidth() const;
  float GetHeight() const;

  float GetLeft() const;
  float GetBottom() const;
  float GetRight() const;
  float GetTop() const;

  void SetWidth(const float& width);
  void SetHeight(const float& hegiht);

protected:
  float m_Width;
  float m_Height;
};

class Movable : public Box2F
{
public:
  Movable(float speedX = 0, float speedY = 0, float X = 0, float Y = 0, float width = 0, float height = 0);

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
