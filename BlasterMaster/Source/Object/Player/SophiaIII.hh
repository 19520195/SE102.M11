#pragma once

#include "Engine/Core/Object.hh"
#include "Engine/Renderer/Animation.hh"
#include "Engine/Renderer/Renderer.hh"
#include "Engine/Renderer/Renderable.hh"
#include <memory>

enum SophiaIIIState
{
  SOPHIAIII_IDLE_LEFT,
  SOPHIAIII_WALK_LEFT,
  SOPHIAIII_IDLE_RIGHT,
  SOPHIAIII_WALK_RIGHT,
};

constexpr float SOPHIAIII_SPEED   = 0.1f;
constexpr float SOPHIAIII_GRAVITY = 0.1f;

typedef RenderableObject  SophiaIIIComponent;
typedef SpriteObject      SophiaIIIBodyPart;
typedef AnimationObject   SophiaIIIWheel;

class SophiaIII : public Object
{
public:
  SophiaIII();

  virtual void Update(TimeStep step);

  void SetState(int state);
  
  void Render(TimeStep step);

private: 
  std::unique_ptr<SophiaIIIComponent> m_Barrel;
  std::unique_ptr<SophiaIIIComponent> m_Hammer;
  std::unique_ptr<SophiaIIIComponent> m_Grip;
  std::unique_ptr<SophiaIIIComponent> m_LWheel;
  std::unique_ptr<SophiaIIIComponent> m_RWheel;
};
