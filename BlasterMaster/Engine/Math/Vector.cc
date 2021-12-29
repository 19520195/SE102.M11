#include "Vector.hh"
#include <cmath>
#include <numeric>

Vector2F::Vector2F(float V) : m_X(V), m_Y(V)
{
}

Vector2F::Vector2F(float X, float Y)
{
  m_X = X;
  m_Y = Y;
}

Vector2F::Vector2F(const Vector2F& vector2) :
  m_X(vector2.m_X), m_Y(vector2.m_Y)
{
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

float Vector2F::Abs() const
{
  return std::sqrt(m_X * m_X + m_Y * m_Y);
}

Vector2F Vector2F::GetUnit() const
{
  Vector2F unit;
  if (this->m_X > 0) unit.m_X = 1;
  else if (this->m_X < 0) unit.m_X = -1;
  if (this->m_Y > 0) unit.m_Y = 1;
  else if (this->m_Y < 0) unit.m_Y = -1;
  return unit;
}

Vector2F Vector2F::Infinity()
{
  return Vector2F(
    std::numeric_limits<float>::infinity(),
    std::numeric_limits<float>::infinity());
}

Vector2F Vector2F::Min(const Vector2F& shl, const Vector2F& shr)
{
  return Vector2F(std::min(shl.m_X, shr.m_X), std::min(shl.m_Y, shr.m_Y));
}

Vector2F Vector2F::Max(const Vector2F& shl, const Vector2F& shr)
{
  return Vector2F(std::max(shl.m_X, shr.m_X), std::max(shl.m_Y, shr.m_Y));
}

Vector2F operator+(const Vector2F& shl, const Vector2F& shr)
{
  return Vector2F(shl.m_X + shr.m_X, shl.m_Y + shr.m_Y);
}

Vector2F operator-(const Vector2F& shl, const Vector2F& shr)
{
  return Vector2F(shl.m_X - shr.m_X, shl.m_Y - shr.m_Y);
}

Vector2F operator*(const Vector2F& shl, const Vector2F& shr)
{
  return Vector2F(shl.m_X * shr.m_X, shl.m_Y * shr.m_Y);
}

Vector2F operator/(const Vector2F& shl, const Vector2F& shr)
{
  return Vector2F(shl.m_X / shr.m_X, shl.m_Y / shr.m_Y);
}

bool operator!=(const Vector2F& shl, const Vector2F& shr)
{
  return shl.m_X != shr.m_X && shl.m_Y != shr.m_Y;
}
