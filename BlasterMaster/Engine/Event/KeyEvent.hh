#pragma once
#define DIRECTINPUT_VERSION 0x0800

#include <Windows.h>
#include <dinput.h>
#include <d3dx9.h>

#include <memory>

constexpr int KEYBOARD_BUFFER_SIZE = 1024;

class KeyEvent
{
public:
	virtual void KeyState(BYTE* state) = 0;
	virtual void OnKeyDown(int code) = 0;
	virtual void OnKeyUp(int code) = 0;
};

class KeyboardHandler
{
public:
  KeyboardHandler() = default;
  
  void Init(HWND window);
  void ProcKeyboard();
  
  bool IsKeyDown(int keycode)
  {
    return (m_KeyStates[keycode] & 0x80) > 0;
  }

  static KeyboardHandler* GetInstance();

public:
  BYTE               m_KeyStates[256];
  DIDEVICEOBJECTDATA m_KeyEvents[KEYBOARD_BUFFER_SIZE];
  KeyEvent*          m_KeyHandler;

private:
  static std::shared_ptr<KeyboardHandler> m_Instance;
};
