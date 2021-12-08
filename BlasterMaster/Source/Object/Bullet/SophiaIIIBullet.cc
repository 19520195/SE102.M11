#include "SophiaIIIBullet.hh"
#include "Object/Object.hh"
#include <algorithm>

SophiaIIIBullet::SophiaIIIBullet(bool isVertical)
{
  this->m_Width  = S3BULLET_SIZE1;
  this->m_Height = S3BULLET_SIZE0;
  this->m_SpeedX = S3BULLET_SPEED;
  this->m_SpeedY = 0;

  if (isVertical)
  {
    std::swap(this->m_Width, this->m_Height);
    std::swap(this->m_SpeedX, this->m_SpeedY);
  }

  this->m_ArriveTime = 0;
}

TimeStep SophiaIIIBullet::GetArriveTime() const
{
  return m_ArriveTime;
}

void SophiaIIIBullet::SetArriveTime(TimeStep arrive)
{
  m_ArriveTime = arrive;
}

void SophiaIIIBullet::Update(TimeStep elapsed, std::vector<Object*> objects)
{
  std::sort(objects.begin(), objects.end(), [](Object* shl, Object* shr) {
    return shl->GetX() < shr->GetX();
  });

  for (size_t i = 0; i < objects.size(); ++i)
  {
    auto& object = objects[i];
    if (!object->IsDied())
    {
      bool killed = Collision::AABB(*this, *object);
      if (!killed)
      {
        float deltaTime = Collision::SweptAABB(*this, *object);
        killed = (0 <= deltaTime && deltaTime <= elapsed);
      }

      if (killed)
      {
        this->Die();
        if (dynamic_cast<Enemy*>(object))
          object->Die();
        return;
      }
    }
  }

  Bullet::Update(elapsed);
}

void SophiaIIIBullet::Render(TimeStep elapsed)
{
  SpriteBase::GetInstance()
    ->Get(m_SpeedX < 0 ? SPRID_S3_LEFT_BULLET : SPRID_S3_RIGHT_BULLET)
    ->Render(m_X, m_Y);
}
