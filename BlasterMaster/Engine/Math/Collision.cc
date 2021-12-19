#include "Collision.hh"
#include <algorithm>
#include <limits>

Movable::Movable(float speedX, float speedY, float X, float Y, float width, float height) : Box2F(X, Y, width, height)
{
  m_SpeedX = speedX;
  m_SpeedY = speedY;
}

Movable::Movable(Vector2F speed, Box2F bounding) : Box2F(bounding)
{
  m_SpeedX = speed.GetX();
  m_SpeedY = speed.GetY();
}

float Movable::GetSpeedX() const
{
  return m_SpeedX;
}

float Movable::GetSpeedY() const
{
  return m_SpeedY;
}

Vector2F Movable::GetVelocity() const
{
  return Vector2F(m_SpeedX, m_SpeedY);
}

Movable Movable::GetMove(float delta) const
{
  Vector2F velocity = GetVelocity();
  return Movable(velocity,
                 Box2F(m_X + velocity.GetX() * delta,
                       m_Y + velocity.GetY() * delta,
                       m_Width,
                       m_Height));
}

void Movable::Move(float delta)
{
  m_X += m_SpeedX * delta; 
  m_Y += m_SpeedY * delta; 
}

bool Collision::IsCollideX(const Movable& object, const Movable& other)
{
  return
    std::abs(object.GetLeft() - other.GetRight()) < TIME_EPSILON ||
    std::abs(object.GetRight() - other.GetLeft()) < TIME_EPSILON;
}

bool Collision::IsCollideY(const Movable& object, const Movable& other)
{
  return
    std::abs(object.GetBottom() - other.GetTop()) < TIME_EPSILON ||
    std::abs(object.GetTop() - other.GetBottom()) < TIME_EPSILON;
}

bool Collision::AABB(const Movable& object, const Movable& other)
{
  return other.GetLeft  () <= object.GetRight () &&
         other.GetRight () >= object.GetLeft  () &&
         other.GetTop   () >= object.GetBottom() &&
         other.GetBottom() <= object.GetTop   () ;
}

float Collision::SweptAABB(const Movable& object, const Movable& other)
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

  float entryTime = std::max(entryTimeX, entryTimeY);
  float exitTime  = std::min(exitTimeX , exitTimeY );

  if (entryTime > exitTime || entryTime < 0.0f)
    return -1.0f;

  Movable moved(object);
  moved.Move(entryTime);
  if (!AABB(moved, other))
    return -1.0f;

  return entryTime; 
}
