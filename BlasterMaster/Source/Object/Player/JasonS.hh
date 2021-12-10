#pragma once
#include "Player.hh"

constexpr float JASONS_WIDTH  =  6.f;
constexpr float JASONS_HEGIHT = 18.f;
constexpr float JASONS_SPEED  =  0.03f;

class JasonSKeyboard;

class JasonS : public Player
{
public:
  JasonS();

  void SetState(int state);

  KeyboardEvent* GetKeyboard();
  void Render(TimeStep elapsed);

private:
  std::unique_ptr<JasonSKeyboard> m_Keyboard;
};

class JasonSKeyboard : public KeyboardEvent
{
public:
  JasonSKeyboard() = delete;
  JasonSKeyboard(JasonS* player);

  void KeyState(BYTE* state);
  void OnKeyDown(int code);
  void OnKeyUp(int code);

private:
  JasonS* m_JasonS;
};
