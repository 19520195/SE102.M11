#pragma once

#include "Engine/Debug/Debug.hh"
#include "Vector.hh"

class Box : public Vector2D
{
public:
  Box(float X = 0, float Y = 0, float width = 0, float height = 0); 

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

class Movable : public Box
{
public:
  Movable(float speedX = 0, float speedY = 0, float X = 0, float Y = 0, float width = 0, float height = 0);

  float GetSpeedX() const;
  float GetSpeedY() const;

protected:
  float m_SpeedX;
  float m_SpeedY;
};

class Collision
{
public:
  static bool IsColliding(const Movable& object, const Movable& other);
  static float SweptAABB(const Movable& object, const Movable& other);
};
