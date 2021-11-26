#pragma once

#include "../Object.hh"
#include "Engine/Renderer/Animation.hh"
#include "Engine/Renderer/Renderer.hh"
#include <memory>

enum SophiaIIIState
{
  SOPHIAIII_IDLE_LEFT,
  SOPHIAIII_IDLE_RIGHT,

  SOPHIAIII_WALK_LEFT,
  SOPHIAIII_WALK_RIGHT,
};

constexpr float SOPHIAIII_SPEED = 0.2F;

class SophiaIIIComponent : public Object
{
public:
  void Render() 
  {
    AnimationBase::Get()->Get(m_AnimationID)->Render(m_X, m_Y);
  }
};

class SophiaIII : public Object
{
public:
  SophiaIII() = default;

  void SetState(int state);
  
  void Render();

private:
  // size_t m_BarrelAID;
  // size_t m_HammerAID;
  // size_t m_GripAID;
  // size_t m_WheelAID;

public: // DEBUG // 
  std::unique_ptr<Object> m_Barrel;
  std::unique_ptr<Object> m_Hammer;
  std::unique_ptr<Object> m_Grip;
  std::unique_ptr<Object> m_LWheel;
  std::unique_ptr<Object> m_RWheel;
};
