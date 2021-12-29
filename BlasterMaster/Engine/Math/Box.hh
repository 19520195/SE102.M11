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

  Vector2F GetCenter() const;
  Vector2F GetLocation() const;
  Vector2F GetSize() const;

  void SetWidth(const float& width);
  void SetHeight(const float& hegiht);

  void SetCenter(const Vector2F& location);
  virtual void SetLocation(const Vector2F& location);
  virtual void SetLocation(float X, float Y);
  virtual void SetSize(const Vector2F& size);
  virtual void SetSize(float width, float height);

protected:
  float m_Width;
  float m_Height;
};
