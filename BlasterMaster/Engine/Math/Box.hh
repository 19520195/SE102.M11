#pragma once
#include "Vector.hh"

class Box2F : public Vector2F
{
public:
  Box2F(float X = 0, float Y = 0, float width = 0, float height = 0);
  Box2F(Vector2F location, float width, float height);

  float GetWidth() const;
  float GetHeight() const;

  float GetLeft() const;
  float GetBottom() const;
  float GetRight() const;
  float GetTop() const;

  void SetWidth(const float& width);
  void SetHeight(const float& hegiht);

  void SetLocation(float X, float Y);
  void SetSize(float width, float height);

protected:
  float m_Width;
  float m_Height;
};
