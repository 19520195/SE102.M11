#pragma once

class Vector2F
{
public:
  Vector2F(float X = 0, float Y = 0);
  
  void SetX(float X); 
  void SetY(float Y); 
  void SetXY(float X, float Y); 

  float GetX() const;
  float GetY() const;

  friend Vector2F operator+(const Vector2F& shl, const Vector2F& shr);
  friend bool operator!=(const Vector2F& shl, const Vector2F& shr);

  static Vector2F Infinity();

protected:
  float m_X;
  float m_Y;
};
