#pragma once

#include "Engine/Core/TimeStep.hh"
#include "Engine/Math/Math.hh"

class Object : public Vector2D
{
public:
  Object();
  ~Object() = default;

  void SetPos(float X, float Y);
  void SetSpeed(float speedX, float speedY);
  void SetState(int state);

  void GetPos(float& X, float& Y);
  void GetSpeed(float& speedX, float& speedY);
  int GetState();

  void Update(TimeStep step);
  virtual void Render() = 0;

protected:
  // float m_X;
  // float m_Y;
  float m_SpeedX;
  float m_SpeedY;

  int m_State;
};

#include "Player/SophiaIII.hh"
