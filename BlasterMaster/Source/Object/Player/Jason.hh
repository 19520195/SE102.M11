#pragma once
#include "Player.hh"

enum class JasonWalkState
{
  IdleUp,
  IdleLeft,
  IdleDown,
  IdleRight,

  WalkUp,
  WalkLeft,
  WalkDown,
  WalkRight,
};

class Jason : public Player
{
public:
  Jason();
  JasonWalkState GetWalkState() const;
  void SetWalkState(const JasonWalkState& ws);

private:
  JasonWalkState m_WalkState;
};

class JasonKeyboard : public KeyboardEvent
{
public:
  enum Key
  {
    KUp    = DIK_UP,
    KLeft  = DIK_LEFT,
    KDown  = DIK_DOWN,
    KRight = DIK_RIGHT,
  };

  JasonKeyboard() = delete;
  JasonKeyboard(Jason* jason);
  void KeyState(BYTE* keyboard);

private:
  Jason* m_Jason;
};
