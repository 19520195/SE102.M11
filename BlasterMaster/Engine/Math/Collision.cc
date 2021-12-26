#include "Collision.hh"
#include <algorithm>
#include <limits>

Movable::Movable(float speedX, float speedY, float X, float Y, float width, float height) : 
  Box2F(X, Y, width, height), m_Velocity(speedX, speedY), m_Acceleration(0, 0)
{
}

Movable::Movable(Vector2F speed, Box2F bounding) : 
  Box2F(bounding), m_Velocity(speed), m_Acceleration(0, 0)
{
}

float Movable::GetSpeedX() const
{
  return m_Velocity.GetX();
}

float Movable::GetSpeedY() const
{
  return m_Velocity.GetY();
}

Vector2F Movable::GetVelocity() const
{
  return Vector2F(m_Velocity.GetX(), m_Velocity.GetY());
}

void Movable::SetVelocity(const Vector2F& velocity)
{
  m_Velocity = velocity;
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
  m_X += m_Velocity.GetX() * delta; 
  m_Y += m_Velocity.GetY() * delta; 
}

bool Collision::IsCollideX(const Box2F& object, const Box2F& other)
{
  return
    std::abs(object.GetLeft() - other.GetRight()) < TIME_EPSILON ||
    std::abs(object.GetRight() - other.GetLeft()) < TIME_EPSILON;
}

bool Collision::IsCollideY(const Box2F& object, const Box2F& other)
{
  return
    std::abs(object.GetBottom() - other.GetTop()) < TIME_EPSILON ||
    std::abs(object.GetTop() - other.GetBottom()) < TIME_EPSILON;
}

bool Collision::AABB(const Box2F& object, const Box2F& other)
{
  return other.GetLeft  () <= object.GetRight () &&
         other.GetRight () >= object.GetLeft  () &&
         other.GetTop   () >= object.GetBottom() &&
         other.GetBottom() <= object.GetTop   () ;
}

float Collision::SweptAABB(const Movable& object, const Movable& other)
{
  return SweptAABBx(object, other).GetCollisionTime();
}

Collider Collision::SweptAABBx(const Movable& object, const Box2F& other)
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
  float exitTime = std::min(exitTimeX, exitTimeY);

  Collider collider;
  collider.m_DeltaTime = -1.f;
  collider.m_Direction = Collider::Direction::None;

  if (entryTime > exitTime || entryTime < 0.0f)
    return collider;

  Movable moved(object);
  moved.Move(entryTime);
  if (!AABB(moved, other))
    return collider;

  collider.m_DeltaTime = Vector2F(entryTimeX, entryTimeY);
  if (entryTime == entryTimeX)
    collider.m_Direction = (object.GetSpeedX() > 0 ? Collider::Direction::Right : Collider::Direction::Left);  
  else collider.m_Direction = (object.GetSpeedY() > 0 ? Collider::Direction::Top : Collider::Direction::Bottom);  
  return collider;
}

Vector2F Collider::GetDeltaTime() const
{
  return m_DeltaTime;
}

Collider::Direction Collider::GetDirection() const
{
  return m_Direction;
}

float Collider::GetCollisionTime() const
{
  return std::max(m_DeltaTime.GetX(), m_DeltaTime.GetY());
}
