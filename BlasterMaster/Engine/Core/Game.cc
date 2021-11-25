#include "Game.hh"

SophiaIII R_SophiaIII;
LPDIRECTINPUT8			 di;
LPDIRECTINPUTDEVICE8 didv;

std::shared_ptr<Game> Game::s_Instance = std::make_shared<Game>();

Game::~Game()
{
  Renderer::CleanDirectX3D();
}

void Game::InitKeyboard()
{
  HRESULT
    hr = DirectInput8Create
    (
      (HINSTANCE)GetWindowLong(Game::GetInstance()->m_Window->GetHandle(), GWL_HINSTANCE),
      DIRECTINPUT_VERSION,
      IID_IDirectInput8, (VOID**)&di, NULL
    );

  if (hr != DI_OK)
  {
    OutputDebugString(L"[ERROR] DirectInput8Create failed!\n");
    return;
  }

  hr = di->CreateDevice(GUID_SysKeyboard, &didv, NULL);

  // TO-DO: put in exception handling
  if (hr != DI_OK)
  {
    OutputDebugString(L"[ERROR] CreateDevice failed!\n");
    return;
  }

  hr = didv->SetDataFormat(&c_dfDIKeyboard);
  hr = didv->SetCooperativeLevel(Game::GetInstance()->m_Window->GetHandle(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
  DIPROPDWORD dipdw;

  dipdw.diph.dwSize = sizeof(DIPROPDWORD);
  dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
  dipdw.diph.dwObj = 0;
  dipdw.diph.dwHow = DIPH_DEVICE;
  dipdw.dwData = KEYBOARD_BUFFER_SIZE;

  hr = didv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
  hr = didv->Acquire();
  if (hr != DI_OK)
  {
    OutputDebugString(L"[ERROR] DINPUT8::Acquire failed!\n");
    return;
  }

  OutputDebugString(L"[INFO] Keyboard has been initialized successfully\n");
}

void Game::Create(int width, int height, std::wstring title, HINSTANCE hInstance, int nCmdShow)
{
  m_Window = std::make_unique<Window>();
  m_Window->Create(width, height, title, hInstance);
  m_Window->Show(nCmdShow);

  Renderer::InitDirectX3D(m_Window->GetHandle(), width / OX_SCREEN_ZOOM, height / OX_SCREEN_ZOOM);
  m_KeyHandler = new SampleKeyEvent();
  InitKeyboard();
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
      ProcKeyboard();
      Renderer::Render();
    }
  }
}

void Game::Update(TimeStep timestep)
{
  R_SophiaIII.Update(timestep);
}

 void Game::ProcKeyboard()
{
  HRESULT hr;
  
  // Collect all key states first
  hr = didv->GetDeviceState(sizeof(keyStates), keyStates);
  if (FAILED(hr))
  {
    // If the keyboard lost focus or was not acquired then try to get control back.
    if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
    {
      HRESULT h = didv->Acquire();
      if (h == DI_OK)
      {
        OutputDebugString(L"[INFO] Keyboard re-acquired!\n");
      }
      else return;
    }
    else
    {
      //OutputDebugString(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hr);
      return;
    }
  }

  m_KeyHandler->KeyState((BYTE*)&keyStates);



  // Collect all buffered events
  DWORD dwElements = KEYBOARD_BUFFER_SIZE;
  hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), keyEvents, &dwElements, 0);
  if (FAILED(hr))
  {
    //OutputDebugString(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
    return;
  }

  // Scan through all buffered events, check if the key is pressed or released
  for (DWORD i = 0; i < dwElements; i++)
  {
    int KeyCode = keyEvents[i].dwOfs;
    int KeyState = keyEvents[i].dwData;
    if ((KeyState & 0x80) > 0)
      m_KeyHandler->OnKeyDown(KeyCode);
    else
      m_KeyHandler->OnKeyUp(KeyCode);
  }
}

Game* Game::GetInstance()
{
  return s_Instance.get();
}
