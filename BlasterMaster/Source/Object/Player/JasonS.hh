#pragma once
#include "Player.hh"

constexpr float JASONS_WIDTH  =  8.f;
constexpr float JASONS_HEGIHT = 16.f;

constexpr float JASONS_WALK    =  0.1100f;
constexpr float JASONS_JUMP    = -444.f;
constexpr float JASONS_GRAVITY = -0.0005f;

enum class JasonSWalkState : uint32_t
{
  IdleLeft,
  IdleRight,

  WalkLeft,
  WalkRight,
};

class JasonS : public Player
{
public:
  JasonS() = delete;
  JasonS(Player* owner);

  Player* GetOwner();
  JasonSWalkState GetCustomState() const;

  void SetWalkState(JasonSWalkState s);

  void OnCollide(const Ref<Collision2D>& collision) override;

private:
  Player*         m_Owner;
  JasonSWalkState m_WalkState;
};

class JasonSKeyboard : public KeyboardEvent
{
public:
  enum Key
  {
    KLeft  = DIK_LEFT,
    KRight = DIK_RIGHT,
    KJump  = DIK_X,
    KEnter = DIK_LSHIFT,
  };

  JasonSKeyboard() = delete;
  JasonSKeyboard(JasonS* jason);

  void KeyState(BYTE* keyboard) override;
  void OnKeyDown(int keycode) override;

private:
  void HandleWalk(BYTE* keyboard);
  void HandleJump(BYTE* keyboard);
  void HandleEnter(int keycode);

private:
  JasonS* m_JasonS;
};
