#pragma once
#include "Player.hh"

class Jason : public Player
{
public:
  Jason();

  void SetBehavior(const Behavior& state) override;
  // void Render(TimeStep elapsed);
};

class JasonKeyboard : public KeyboardEvent
{
public:
  JasonKeyboard() = delete;
  JasonKeyboard(Jason* player);
  void KeyState(BYTE* state);

private:
  Jason* m_Player;
};
