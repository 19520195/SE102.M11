#pragma once
#include "Bullet.hh"

constexpr float S3BULLET_SIZE0 =  8.0f;
constexpr float S3BULLET_SIZE1 = 24.0f;
constexpr float S3BULLET_SPEED =  0.2f;


class SophiaIIIBullet : public Bullet
{
public:
  SophiaIIIBullet() = delete; 
  ~SophiaIIIBullet() = default;

  SophiaIIIBullet(bool isVertical);

private:
  //
};
