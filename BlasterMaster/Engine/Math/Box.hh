#pragma once
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
