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

typedef RenderableObject SophiaIIIComponent;

class SophiaIIIBodyPart : public SpriteObject
{
public:
  // 

private:
  // 
};

class SophiaIIIWheel : public AnimationObject
{
public:
  // 

private:
  // 
};

class SophiaIII : public Object
{
public:
  SophiaIII();

  void SetState(int state);
  
  void Render();

public: // DEBUG // 
  std::unique_ptr<SophiaIIIComponent> m_Barrel;
  std::unique_ptr<SophiaIIIComponent> m_Hammer;
  std::unique_ptr<SophiaIIIComponent> m_Grip;
  std::unique_ptr<SophiaIIIComponent> m_LWheel;
  std::unique_ptr<SophiaIIIComponent> m_RWheel;
};
