#include "Game.hh"

Ref<Game> Game::s_Instance = CreateRef<Game>();

Game::~Game()
{
  Renderer::CleanDirectX3D();
}

Ref<Scene> Game::GetScene() const
{
  return m_Scene; 
}

TimeStep Game::GetLastFrameTime() const
{
  return m_LastFrameTime;
}

TimeStep Game::GetElapsedTime() const
{
  return m_ElapsedTime;
}

void Game::SetScene(Ref<Scene> scene)
{
  if ((m_Scene = scene) != nullptr)
    Input::GetInstance()->SetKeyHandler(m_Scene->GetKeyboardHandler());
}

void Game::Create(int width, int height, std::wstring title, HINSTANCE hInstance, int nCmdShow)
{
  m_Window = std::make_unique<Window>();
  m_Window->Create(width * ENGINE_SCREEN_ZOOM, height * ENGINE_SCREEN_ZOOM, title, hInstance);
  m_Window->Show(nCmdShow);

  Renderer::InitDirectX3D(m_Window->GetHandle(), width, height);
  Input::GetInstance()->InitKeyboard(m_Window->GetHandle());
}

void Game::Run()
{
  m_LastFrameTime = static_cast<TimeStep>(GetTickCount64());

  MSG msg;
  while (m_Running)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);

      if (msg.message == WM_QUIT)
      {
        m_Running = false;
        break;
      }
    }
   
    TimeStep currentFrameTime = static_cast<TimeStep>(GetTickCount64());
    m_ElapsedTime = currentFrameTime - m_LastFrameTime;
    m_LastFrameTime = currentFrameTime;
    if (m_ElapsedTime < ENGINE_FRAME_STEP)
    {
      Sleep(static_cast<DWORD>(ENGINE_FRAME_STEP - m_ElapsedTime));
    }
    else
    {
      if (m_Scene)
      {
        Input::GetInstance()->ProcKeyboard();
        m_Scene->Update(m_ElapsedTime);
        Renderer::Render(m_ElapsedTime);
      }
    }
  }
}

Ref<Game> Game::GetInstance()
{
  return s_Instance;
}
