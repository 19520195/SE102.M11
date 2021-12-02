#pragma once

#include "../Object.hh"
#include "Engine/Core/Input.hh"
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
constexpr float SOPHIAIII_GRAVITY = 0.0001f;

typedef RenderableObject  SophiaIIIComponent;
typedef SpriteObject      SophiaIIIBodyPart;
typedef AnimationObject   SophiaIIIWheel;

class SophiaIII : public Player
{
public:
  SophiaIII();

  void SetState(int state);
  
  virtual void Update(TimeStep elapsed, std::vector<Object*> objects);
  virtual void Render(TimeStep elapsed);

private: 
  std::unique_ptr<SophiaIIIComponent> m_Barrel;
  std::unique_ptr<SophiaIIIComponent> m_Hammer;
  std::unique_ptr<SophiaIIIComponent> m_Grip;
  std::unique_ptr<SophiaIIIComponent> m_LWheel;
  std::unique_ptr<SophiaIIIComponent> m_RWheel;
};

class SophiaIIIKeyboardEvent : public KeyboardEvent
{
public:
  virtual void KeyState(BYTE* state);
  virtual void OnKeyUp(int code);
  virtual void OnKeyDown(int code);

public: // DEBUG //
  SophiaIII* m_SophiaIII; 
};
