#include "Box.hh"

Box2F::Box2F(float X, float Y, float width, float height) : Vector2F(X, Y)
{
  m_Width = width;
  m_Height = height;
}

Box2F::Box2F(Vector2F location, float width, float height)
  : Vector2F(location), m_Width(width), m_Height(height)
{
}

float Box2F::GetLeft() const
{
  return m_X;
}

float Box2F::GetBottom() const
{
  return m_Y;
}

float Box2F::GetRight() const
{
  return m_X + m_Width;
}

float Box2F::GetTop() const
{
  return m_Y + m_Height;
}

Vector2F Box2F::GetCenter() const
{
  return Vector2F(m_X + m_Width / 2, m_Y + m_Height / 2);
}

Vector2F Box2F::GetLocation() const
{
  return static_cast<Vector2F>(*this);
}

Vector2F Box2F::GetSize() const
{
  return Vector2F(m_Width, m_Height);
}

float Box2F::GetWidth() const
{
  return m_Width;
}

float Box2F::GetHeight() const
{
  return m_Height;
}

void Box2F::SetWidth(const float& width)
{
  m_Width = width;
}

void Box2F::SetHeight(const float& hegiht)
{
  m_Height = hegiht;
}

void Box2F::SetCenter(const Vector2F& location)
{
  SetLocation(location - (Vector2F(m_Width, m_Height) / 2.f));
}

void Box2F::SetLocation(const Vector2F& location)
{
  m_X = location.GetX();
  m_Y = location.GetY();
}

void Box2F::SetLocation(float X, float Y)
{
  m_X = X;
  m_Y = Y;
}

void Box2F::SetSize(const Vector2F& size)
{
  m_Width = size.GetX();
  m_Height = size.GetY();
}

void Box2F::SetSize(float width, float height)
{
  m_Width = width;
  m_Height = height;
}
