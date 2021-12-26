#include "SophiaIIIBullet.hh"
#include "Object/Enemy/Enemy.hh"
#include "Object/Player/SophiaIII.hh"
#include <algorithm>

SophiaIIIBullet::SophiaIIIBullet(bool isVertical)
{
  this->m_Width  = S3BULLET_SIZE1;
  this->m_Height = S3BULLET_SIZE0;
  if (isVertical) std::swap(this->m_Width, this->m_Height);
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
  if (this->IsDied()) return;
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
        if (dynamic_cast<Brick*>(object))
          return this->Die();
        
        if (Enemy* enemy = dynamic_cast<Enemy*>(object))
        {
          if (enemy->IsActivated())
          {
            object->Die();
            this->Die();
            return;
          }
        }
      }
    }
  }

  Bullet::Update(elapsed);
}

void SophiaIIIBullet::Render(TimeStep elapsed)
{
  size_t spriteID = 0;
  if (m_Velocity.GetX())
    spriteID = m_Velocity.GetX() < 0 ? SPRID_S3_LEFT_BULLET : SPRID_S3_RIGHT_BULLET;
  else spriteID = SPRID_S3_UP_BULLET;
  SpriteBase::GetInstance()->Get(spriteID)->Render(m_X, m_Y);
}
