#include "Game.hh"

SophiaIII R_SophiaIII;

std::shared_ptr<Game> Game::s_Instance = std::make_shared<Game>();

Game::~Game()
{
  Renderer::CleanDirectX3D();
}

void Game::Create(int width, int height, std::wstring title, HINSTANCE hInstance, int nCmdShow)
{
  m_Window = std::make_unique<Window>();
  m_Window->Create(width * OX_SCREEN_ZOOM, height * OX_SCREEN_ZOOM, title, hInstance);
  m_Window->Show(nCmdShow);

  Renderer::InitDirectX3D(m_Window->GetHandle(), width, height);
  Input::GetInstance()->InitKeyboard(m_Window->GetHandle());
  Input::GetInstance()->SetKeyHandler(new SampleKeyEvent());
}

void Game::Run()
{
  m_LastFrameTime = GetTickCount64();

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

    TimeStep currentFrameTime = GetTickCount64();
    TimeStep step = currentFrameTime - m_LastFrameTime;
    m_LastFrameTime = currentFrameTime;

    if (step < ENGINE_FRAME_STEP) Sleep((DWORD)(ENGINE_FRAME_STEP - step));
    else
    {
      Update(step);
      Input::GetInstance()->ProcKeyboard();
      Renderer::Render(step);
    }
  }
}

void Game::Update(TimeStep timestep)
{
  R_SophiaIII.Update(timestep);
}

Game* Game::GetInstance()
{
  return s_Instance.get();
}
