#pragma once
#include "JasonS.hh"
#include "Object/Object.hh"
#include "Object/Bullet/SophiaIIIBullet.hh"
#include "Engine/Core/Input.hh"
#include "Engine/Renderer/Animation.hh"
#include "Engine/Renderer/Renderer.hh"
#include <deque>
#include <memory>

constexpr float SOPHIAIII_WIDTH  = 24.f;
constexpr float SOPHIAIII_HEIGHT = 18.f;

constexpr float SOPHIAIII_SPEED     = 0.1500f;
constexpr float SOPHIAIII_JUMPSPEED = 0.2585f;
constexpr float SOPHIAIII_GRAVITY   = 0.0005f;

class JasonS;

enum SophiaIIIKBS : uint32_t
{
  Open  = DIK_LSHIFT,
  Jump  = DIK_X,
  Shoot = DIK_C,

  Up    = DIK_UP,
  Left  = DIK_LEFT,
  Down  = DIK_DOWN,
  Right = DIK_RIGHT,
};

class SophiaIII : public Player
{
public:
  SophiaIII();

  TimeStep GetLastBulletTime() const;

  void SetState(int state);
  
  Ref<SophiaIIIBullet> CreateBullet();
  Scope<JasonS> CreateJason();

  void OnCollide(const Ref<Collision2D>& collision) override;

  virtual void Update(TimeStep elapsed, std::vector<Ref<Object>> objects);
  virtual void Render(TimeStep elapsed);

private:
  Vector2F CollideWithBrick(Brick* brick, float deltaCollide);

private:
  Scope<Object> m_Barrel;
  Scope<Object> m_Hammer;
  Scope<Object> m_Grip;
  Scope<Object> m_LWheel;
  Scope<Object> m_RWheel;

  std::deque<TimeStep> m_BulletTimes;
};

class SophiaIIIKeyboardEvent : public KeyboardEvent
{
public:
  SophiaIIIKeyboardEvent() = delete;
  SophiaIIIKeyboardEvent(SophiaIII* player);

  virtual void KeyState(BYTE* state);
  virtual void OnKeyUp(int code);
  virtual void OnKeyDown(int code);

private:
  SophiaIII* m_Player;
};
