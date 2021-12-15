#include "Vector.hh"

Vector2F::Vector2F(float X, float Y)
{
  m_X = X;
  m_Y = Y;
}

void Vector2F::SetX(float X)
{
  m_X = X;
}

void Vector2F::SetY(float Y)
{
  m_Y = Y;
}

void Vector2F::SetXY(float X, float Y)
{
  m_X = X;
  m_Y = Y;
}

float Vector2F::GetX() const
{
  return m_X;
}

float Vector2F::GetY() const
{
  return m_Y;
}

Vector2F operator+(const Vector2F& shl, const Vector2F& shr)
{
  return Vector2F(shl.m_X + shr.m_X, shl.m_Y + shr.m_Y);
}

bool operator!=(const Vector2F& shl, const Vector2F& shr)
{
  return shl.m_X != shr.m_X && shl.m_Y != shr.m_Y;
}
