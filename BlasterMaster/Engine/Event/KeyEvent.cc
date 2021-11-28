#include "KeyEvent.hh"

std::shared_ptr<KeyboardHandler> KeyboardHandler::m_Instance = std::make_shared<KeyboardHandler>(); 

LPDIRECTINPUT8			 di;
LPDIRECTINPUTDEVICE8 didv;

void KeyboardHandler::Init(HWND window)
{
  HRESULT
    hr = DirectInput8Create
    (
      (HINSTANCE)GetWindowLong(window, GWL_HINSTANCE),
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
  hr = didv->SetCooperativeLevel(window, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
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

void KeyboardHandler::ProcKeyboard()
{
  HRESULT hr;

  // Collect all key states first
  hr = didv->GetDeviceState(sizeof(m_KeyStates), m_KeyStates);
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

  m_KeyHandler->KeyState((BYTE*)&m_KeyStates);



  // Collect all buffered events
  DWORD dwElements = KEYBOARD_BUFFER_SIZE;
  hr = didv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_KeyEvents, &dwElements, 0);
  if (FAILED(hr))
  {
    //OutputDebugString(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hr);
    return;
  }

  // Scan through all buffered events, check if the key is pressed or released
  for (DWORD i = 0; i < dwElements; i++)
  {
    int KeyCode = m_KeyEvents[i].dwOfs;
    int KeyState = m_KeyEvents[i].dwData;
    if ((KeyState & 0x80) > 0)
      m_KeyHandler->OnKeyDown(KeyCode);
    else
      m_KeyHandler->OnKeyUp(KeyCode);
  }
}

KeyboardHandler* KeyboardHandler::GetInstance()
{
  return m_Instance.get();
}
