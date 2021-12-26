#pragma once
#include "Enemy.hh"

constexpr float STUKA_WIDTH  = 16.000f;
constexpr float STUKA_HEIGHT = 16.000f;

constexpr float STUKA_SPEED =  0.033f;
constexpr float STUKA_RANGE = 96.000f;

class Stuka : public Enemy 
{
public:
  Stuka();
  void Update(TimeStep elapsed);
  void Render(TimeStep elapsed);

private:
  float m_Trail;
};
