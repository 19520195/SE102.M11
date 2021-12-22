#pragma once
#include "Enemy.hh"

constexpr float EYELET_RANGE = 24.f;
constexpr float EYELET_SPEED =  0.1f;

class Eyelet : public Enemy
{
public:
  Eyelet();
  Trigger* CreateTrigger();
  
  void SetState(int state);
  void SetStartPoint(const Vector2F& point);
 
  void Update(TimeStep elasped);
  void Render(TimeStep elapsed);

private:
  uint32_t m_RenderID;
};
