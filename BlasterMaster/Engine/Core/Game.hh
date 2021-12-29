#pragma once
#include "Engine/Debug/Debug.hh"
#include "Engine/Scene/Scene.hh"
#include "Engine/Renderer/Renderer.hh"
#include "Base.hh"
#include "Window.hh"
#include "TimeStep.hh"
#include "Input.hh"
#include <memory>

constexpr TimeStep ENGINE_FPS         = 120;
constexpr TimeStep ENGINE_FRAME_STEP  = 1000 / ENGINE_FPS;
constexpr int      ENGINE_SCREEN_ZOOM = 3;

class Game
{
public:
  Game() = default;
  ~Game();

  Ref<Scene> GetScene();
  TimeStep GetLastFrameTime() const;
  TimeStep GetElapsedTime() const;

  void SetScene(Ref<Scene> scene);
  void SwitchScene(Ref<Scene> scene);

  void Create(int width, int height, std::wstring title, HINSTANCE hInstance, int nCmdShow);
  void Run();

  static Ref<Game> GetInstance();

private:
  Scope<Window> m_Window;
  Ref<Scene>    m_Scene;
  Ref<Scene>    m_NextScene;

  bool     m_Running       = true;
  TimeStep m_LastFrameTime = 0;
  TimeStep m_ElapsedTime   = 0;

  static Ref<Game> s_Instance; 
};
