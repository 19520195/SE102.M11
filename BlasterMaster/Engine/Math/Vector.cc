#include "Vector.hh"

Vector2D::Vector2D(float X, float Y)
{
  m_X = X;
  m_Y = Y;
}

void Vector2D::SetXY(float X, float Y)
{
  m_X = X;
  m_Y = Y;
}

float Vector2D::GetX() const
{
  return m_X;
}

float Vector2D::GetY() const
{
  return m_Y;
}

Vector2D operator+(const Vector2D& shl, const Vector2D& shr)
{
  return Vector2D(shl.m_X + shr.m_X, shl.m_Y + shr.m_Y);
}

bool operator!=(const Vector2D& shl, const Vector2D& shr)
{
  return shl.m_X != shr.m_X && shl.m_Y != shr.m_Y;
}
