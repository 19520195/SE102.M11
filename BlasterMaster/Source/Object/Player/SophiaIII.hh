#pragma once

#include "Engine/Core/Object.hh"
#include "Engine/Renderer/Animation.hh"
#include "Engine/Renderer/Renderer.hh"
#include "Engine/Renderer/Renderable.hh"
#include <memory>

enum SophiaIIIState
{
  SOPHIAIII_IDLE_LEFT,
  SOPHIAIII_IDLE_RIGHT,

  SOPHIAIII_WALK_LEFT,
  SOPHIAIII_WALK_RIGHT,
};

constexpr float SOPHIAIII_SPEED = 0.2F;

class SophiaIIIComponent : public Object, public SpriteRender
{
public:
  void Render()
  {
    SpriteRender::Render(m_X, m_Y);
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
  std::unique_ptr<SophiaIIIComponent> m_Barrel;
  std::unique_ptr<SophiaIIIComponent> m_Hammer;
  std::unique_ptr<SophiaIIIComponent> m_Grip;
  std::unique_ptr<SophiaIIIComponent> m_LWheel;
  std::unique_ptr<SophiaIIIComponent> m_RWheel;
};
