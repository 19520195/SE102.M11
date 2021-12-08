#include "SophiaIIIBullet.hh"

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
