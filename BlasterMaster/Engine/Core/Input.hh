#pragma once
#define DIRECTINPUT_VERSION 0x0800

#include "Engine/Debug/Debug.hh"
#include "Engine/Event/KeyboardEvent.hh"

#include <Windows.h>
#include <dinput.h>
#include <d3dx9.h>

#include <memory>

constexpr int KEYBOARD_BUFFER_SIZE = 1024;
constexpr int KEYSTATE_BUFFER_SIZE = 256;

#ifndef IS_KEYDOWN
#define IS_KEYDOWN(KEYSTATE, KEYCODE) (bool)(KEYSTATE[KEYCODE] & 0x80)
#endif // IS_KEYDOWN

class Input
{
public:
  Input() = default;

  void SetKeyHandler(KeyboardEvent* handler);

  void InitKeyboard(HWND hWnd);
  void ProcKeyboard();

  bool IsKeyDown(int keycode);

  static Input* GetInstance();

private:
  IDirectInput8*			 m_DirectInput;
  IDirectInputDevice8* m_DirectInputDevice;

  BYTE               m_KeyStates[KEYSTATE_BUFFER_SIZE];
  DIDEVICEOBJECTDATA m_KeyEvents[KEYBOARD_BUFFER_SIZE];
  KeyboardEvent*     m_KeyHandler;

private:
  static std::shared_ptr<Input> m_Instance;
};
