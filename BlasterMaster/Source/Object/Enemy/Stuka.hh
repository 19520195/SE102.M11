#pragma once
#include "Enemy.hh"

constexpr float STUKA_WIDTH  = 16.000f;
constexpr float STUKA_HEIGHT = 16.000f;

constexpr float STUKA_SPEED =  0.033f;
constexpr float STUKA_RANGE = 64.000f;

enum class StukaState : uint32_t
{
  Left,
  Right,
  Chase,
};

class Stuka : public Enemy 
{
public:
  Stuka();
  void SetTrail(float trail);
  void SetState(const StukaState& state);

  void OnCollide(const Ref<Collision2D>& collision) override;

  void Update() override;
  void Update(TimeStep elapsed);

private:
  StukaState m_CustomState;
  float      m_Trail;
};
