#include "Box.hh"

Box2F::Box2F(float X, float Y, float width, float height) : Vector2F(X, Y)
{
  m_Width = width;
  m_Height = height;
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

float Box2F::GetWidth() const
{
  return m_Width;
}

float Box2F::GetHeight() const
{
  return m_Height;
}

void Box2F::SetLocation(float X, float Y)
{
  m_X = X;
  m_Y = Y;
}

void Box2F::SetWidth(const float& width)
{
  m_Width = width;
}

void Box2F::SetHeight(const float& hegiht)
{
  m_Height = hegiht;
}
