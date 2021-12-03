#include "Collision.hh"
#include <algorithm>
#include <limits>

Box::Box(float X, float Y, float width, float height) : Vector2D(X, Y)
{
  m_Width = width;
  m_Height = height; 
}

float Box::GetTop() const
{
  return m_Y + m_Height;
}

float Box::GetLeft() const
{
  return m_X;
}

float Box::GetBottom() const
{
  return m_Y;
}

float Box::GetRight() const
{
  return m_X + m_Width;
}

void Box::SetWidth(const float& width)
{
  m_Width = width; 
}

void Box::SetHeight(const float& hegiht)
{
  m_Height = hegiht; 
}

Movable::Movable(float speedX, float speedY, float X, float Y, float width, float height) : Box(X, Y, width, height)
{
  m_SpeedX = speedX;
  m_SpeedY = speedY;
}

float Movable::GetSpeedX() const
{
  return m_SpeedX;
}

float Movable::GetSpeedY() const
{
  return m_SpeedY;
}

bool Collision::IsColliding(const Movable& object, const Movable& other)
{
  return other.GetLeft  () <= object.GetRight () &&
         other.GetRight () >= object.GetLeft  () &&
         other.GetTop   () >= object.GetBottom() &&
         other.GetBottom() <= object.GetTop   () ;
}

Vector2D Collision::SweptAABB(const Movable& object, const Movable& other)
{
  // Delta of ENTRY and EXIT
  float entryDeltaX, exitDeltaX;
  float entryDeltaY, exitDeltaY;

  if (object.GetSpeedX() > 0.0f)
  {
    entryDeltaX = other.GetLeft() - object.GetRight();
    exitDeltaX = other.GetRight() - object.GetLeft();
  }
  else
  {
    entryDeltaX = other.GetRight() - object.GetLeft();
    exitDeltaX = other.GetLeft() - object.GetRight();
  }

  if (object.GetSpeedY() > 0.0f)
  {
    entryDeltaY = other.GetBottom() - object.GetTop();
    exitDeltaY = other.GetTop() - object.GetBottom();
  }
  else
  {
    entryDeltaY = other.GetTop() - object.GetBottom();
    exitDeltaY = other.GetBottom() - object.GetTop();
  }

  // Delta of time of X and Y
  float entryTimeX, exitTimeX;
  float entryTimeY, exitTimeY;

  if (object.GetSpeedX() == 0.0f)
  {
    entryTimeX = -std::numeric_limits<float>::infinity();
    exitTimeX = std::numeric_limits<float>::infinity();
  }
  else
  {
    entryTimeX = entryDeltaX / object.GetSpeedX();
    exitTimeX = exitDeltaX / object.GetSpeedX();
  }

  if (object.GetSpeedY() == 0.0f)
  {
    entryTimeY = -std::numeric_limits<float>::infinity();
    exitTimeY = std::numeric_limits<float>::infinity();
  }
  else
  {
    entryTimeY = entryDeltaY / object.GetSpeedY();
    exitTimeY = exitDeltaY / object.GetSpeedY();
  }

  float entryTime = max(entryTimeX, entryTimeY);
  float exitTime  = min(exitTimeX , exitTimeY );

  if (entryTime > exitTime || entryTime < 0.0f)
    return Vector2D(-1.0f, -1.0f);

  Movable entry = object;
  entry.SetXY(entry.GetX() + entryTime * object.GetSpeedX(), entry.GetY() + entryTime * object.GetSpeedY());
  if (!IsColliding(entry, other))
    return Vector2D(-1.0f, -1.0f);

  DEBUG_MSG(L"Time = %f %f\n", entryTimeX, entryTimeY);

  // entryTimeX = max(entryTimeX, 0.0f);
  // entryTimeY = max(entryTimeY, 0.0f);
  return Vector2D(entryTimeX, entryTimeY);
}
