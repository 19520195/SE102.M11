#include "Collision2D.hh"
#include "Engine/Core/Game.hh"

TimeStep Collision2D::GetTime() const
{
  return m_Time;
}

Vector2F Collision2D::GetNormal() const
{
  return m_Normal;
}

Ref<Collider2D> Collision2D::GetCollider() const
{
  return m_Collider;
}

bool Collision2D::AABB(const Box2F& shl, const Box2F& shr)
{
  return shl.GetLeft() <= shr.GetRight() &&
    shl.GetRight() >= shr.GetLeft() &&
    shl.GetTop() >= shr.GetBottom() &&
    shl.GetBottom() <= shr.GetTop();
}

Ref<Collision2D> Collision2D::SweptAABB(const Ref<Collider2D>& shl, const Ref<Collider2D>& shr)
{
  const auto& object = *shl->GetRefer();
  const auto& other = *shr->GetRefer();

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

  TimeStep elapsed = Game::GetInstance()->GetElapsedTime();
  if (entryTime > exitTime || (entryTimeX < 0.0f && entryTimeY < 0.0f) || entryTimeX > elapsed || entryTimeY > elapsed)
    return nullptr;
  
  if (!AABB(object.GetMove(entryTime), other))
    return nullptr;

  auto collision = CreateRef<Collision2D>();
  collision->m_Time = entryTime;
  collision->m_Collider = shr;
  if (entryTimeX > entryTimeY)
    collision->m_Normal = Vector2F(entryDeltaX < 0 ? 1.f : -1.f, 0.f);
  else collision->m_Normal = Vector2F(0, entryDeltaY < 0 ? 1.f : -1.f);
  return collision;
}

bool operator<(const Collision2D& shl, const Collision2D& shr)
{
  return shl.m_Time < shr.m_Time;
}