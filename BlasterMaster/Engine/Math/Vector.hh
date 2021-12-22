#pragma once

class Vector2F
{
public:
  Vector2F(float V = 0);
  Vector2F(float X, float Y);
  
  void SetX(float X); 
  void SetY(float Y); 
  void SetXY(float X, float Y); 

  float GetX() const;
  float GetY() const;

  friend Vector2F operator+(const Vector2F& shl, const Vector2F& shr);
  friend Vector2F operator*(const Vector2F& shl, const Vector2F& shr);
  friend Vector2F operator/(const Vector2F& shl, const Vector2F& shr);
  friend bool operator!=(const Vector2F& shl, const Vector2F& shr);

  static Vector2F Infinity();
  static Vector2F Min(const Vector2F& shl, const Vector2F& shr);
  static Vector2F Max(const Vector2F& shl, const Vector2F& shr);

protected:
  float m_X;
  float m_Y;
};
