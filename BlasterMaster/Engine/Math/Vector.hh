#pragma once

class Vector2D
{
public:
  Vector2D(float X = 0, float Y = 0);
  
  void SetX(float X); 
  void SetY(float Y); 
  void SetXY(float X, float Y); 

  float GetX() const;
  float GetY() const;

  friend Vector2D operator+(const Vector2D& shl, const Vector2D& shr);
  friend bool operator!=(const Vector2D& shl, const Vector2D& shr);

protected:
  float m_X;
  float m_Y;
};
