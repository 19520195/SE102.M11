#pragma once

#include "Object/Object.hh"
#include "Object/Bullet/SophiaIIIBullet.hh"

#include "Engine/Core/Input.hh"
#include "Engine/Renderer/Animation.hh"
#include "Engine/Renderer/Renderer.hh"
#include "Engine/Renderer/Renderable.hh"
#include <deque>
#include <memory>

extern std::vector<bool> DEBUG_COLLISION;

constexpr float SOPHIAIII_WIDTH  = 24.f;
constexpr float SOPHIAIII_HEIGHT = 18.f;

constexpr float SOPHIAIII_SPEED     = 0.1500f;
constexpr float SOPHIAIII_JUMPSPEED = 0.2585f;
constexpr float SOPHIAIII_GRAVITY   = 0.0005f;


typedef RenderableObject  SophiaIIIComponent;
typedef SpriteObject      SophiaIIIBodyPart;
typedef AnimationObject   SophiaIIIWheel;

class SophiaIII : public Player
{
public:
  SophiaIII();

  TimeStep GetLastBulletTime() const;
  std::vector<SophiaIIIBullet*> GetBullets();

  void SetState(int state);
  
  void AddBullet(SophiaIIIBullet* bullet);
  
  SophiaIIIBullet* CreateBullet();

  virtual void Update(TimeStep elapsed, std::vector<Object*> objects);
  virtual void Render(TimeStep elapsed);

private: 
  std::unique_ptr<SophiaIIIComponent> m_Barrel;
  std::unique_ptr<SophiaIIIComponent> m_Hammer;
  std::unique_ptr<SophiaIIIComponent> m_Grip;
  std::unique_ptr<SophiaIIIComponent> m_LWheel;
  std::unique_ptr<SophiaIIIComponent> m_RWheel;

  std::deque<std::unique_ptr<SophiaIIIBullet>> m_Bullets;
};

class SophiaIIIKeyboardEvent : public KeyboardEvent
{
public:
  SophiaIIIKeyboardEvent() = default;

  virtual void KeyState(BYTE* state);
  virtual void OnKeyUp(int code);
  virtual void OnKeyDown(int code);
};
