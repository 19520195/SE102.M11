#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <d3dx9.h>

#include <memory>

#include "Window.hh"
#include "TimeStep.hh"
#include "Engine/Renderer/Renderer.hh"
#include "Engine/Event/KeyEvent.hh"

constexpr int OX_SCREEN_ZOOM = 3;
constexpr int KEYBOARD_BUFFER_SIZE = 1024;

constexpr TimeStep ENGINE_FPS        = 120;
constexpr TimeStep ENGINE_FRAME_STEP = 1000 / ENGINE_FPS;

#include "Source/Object/Player/SophiaIII.hh"
extern SophiaIII R_SophiaIII;

class Game
{
public:
  Game() = default;
  ~Game();

  void InitKeyboard();

  void Create(int width, int height, std::wstring title, HINSTANCE hInstance, int nCmdShow);

  void Run();

  void Update(TimeStep timestep);
 
  void ProcKeyboard();

  static Game* GetInstance();

  bool IsKeyDown(int keycode)
  {
    return (keyStates[keycode] & 0x80) > 0;
  }

private:
  std::unique_ptr<Window> m_Window;
  
  bool     m_Running       = true;
  TimeStep m_LastFrameTime = 0; 

  BYTE  keyStates[256];
  DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];
  KeyEvent* m_KeyHandler;

private:
  static std::shared_ptr<Game> s_Instance; 
};

class SampleKeyEvent : public KeyEvent
{
  void KeyState(BYTE* state)
  {
    SophiaIII* sophiaIII = &R_SophiaIII;

    if (Game::GetInstance()->IsKeyDown(DIK_RIGHT))
      sophiaIII->SetState(SOPHIAIII_WALK_RIGHT);
    else if (Game::GetInstance()->IsKeyDown(DIK_LEFT))
      sophiaIII->SetState(SOPHIAIII_WALK_LEFT);
    else
    {
      if (sophiaIII->GetState() == SOPHIAIII_WALK_LEFT)
        sophiaIII->SetState(SOPHIAIII_IDLE_LEFT);
      else if (sophiaIII->GetState() == SOPHIAIII_WALK_RIGHT)
        sophiaIII->SetState(SOPHIAIII_IDLE_RIGHT);
    }
  }

  void OnKeyDown(int code)
  {
    //
  }

  void OnKeyUp(int code) {
  }
};