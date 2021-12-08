#pragma once
#include "Bullet.hh"

constexpr float S3BULLET_SIZE0 =  8.0f;
constexpr float S3BULLET_SIZE1 = 24.0f;
constexpr float S3BULLET_SPEED =  0.2f;

constexpr float S3_BULLET_TIMEOUT = 2000; // ms
constexpr float S3_BULLET_T3MP    =  300; // ms

class SophiaIIIBullet : public Bullet
{
public:
  SophiaIIIBullet() = delete; 
  ~SophiaIIIBullet() = default;

  SophiaIIIBullet(bool isVertical);

  TimeStep GetArriveTime() const;

  void SetArriveTime(TimeStep arrive);

private:
  TimeStep m_ArriveTime;
};
