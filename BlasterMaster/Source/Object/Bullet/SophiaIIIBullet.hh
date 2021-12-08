#pragma once
#include "Bullet.hh"

constexpr float S3BULLET_SIZE0 =  8.0f;
constexpr float S3BULLET_SIZE1 = 24.0f;
constexpr float S3BULLET_SPEED =  0.3f;

constexpr float S3_BULLET_TIMEOUT = 1000; // ms
constexpr float S3_BULLET_T3MP    =  100; // ms

class SophiaIIIBullet : public Bullet
{
public:
  SophiaIIIBullet() = delete; 
  ~SophiaIIIBullet() = default;

  SophiaIIIBullet(bool isVertical);

  TimeStep GetArriveTime() const;

  void SetArriveTime(TimeStep arrive);

  virtual void Update(TimeStep elapsed, std::vector<Object*> objects);
  virtual void Render(TimeStep elapsed);

private:
  TimeStep m_ArriveTime;
};
