#pragma once
#include "Engine/Debug/Debug.hh"
#include "Engine/Scene/Scene.hh"
#include "Engine/Renderer/Renderer.hh"
#include "Base.hh"
#include "Window.hh"
#include "TimeStep.hh"
#include "Input.hh"
#include <memory>

constexpr int ENGINE_SCREEN_ZOOM =  4;

constexpr TimeStep ENGINE_FPS        = 120;
constexpr TimeStep ENGINE_FRAME_STEP = 1000 / ENGINE_FPS;

class Game
{
public:
  Game() = default;
  ~Game();

  Ref<Scene> GetScene() const;
  TimeStep GetLastFrameTime() const;

  void SetScene(Ref<Scene> scene);

  void Create(int width, int height, std::wstring title, HINSTANCE hInstance, int nCmdShow);

  void Run();

  static Game* GetInstance();

private:
  std::unique_ptr<Window> m_Window;
  
  Ref<Scene> m_Scene;
  bool     m_Running       = true;
  TimeStep m_LastFrameTime = 0;

private:
  static std::shared_ptr<Game> s_Instance; 
};
