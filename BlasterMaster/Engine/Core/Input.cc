#include "Input.hh"

std::shared_ptr<Input> Input::m_Instance = std::make_shared<Input>();

void Input::SetKeyHandler(KeyboardEvent* handler)
{
  m_KeyHandler = handler; 
}

void Input::InitKeyboard(HWND hWnd)
{
  HRESULT hResult;
  hResult = DirectInput8Create(
    GetModuleHandle(NULL),
    DIRECTINPUT_VERSION,
    IID_IDirectInput8,
    reinterpret_cast<void**>(&m_DirectInput),
    NULL);

  if (hResult != DI_OK)
    return DEBUG_MSG(L"[ERROR] DirectInput8Create failed!\n");

  hResult = m_DirectInput->CreateDevice(GUID_SysKeyboard, &m_DirectInputDevice, NULL);
  if (hResult != DI_OK)
    return DEBUG_MSG(L"[ERROR] CreateDevice failed!\n");

  hResult = m_DirectInputDevice->SetDataFormat(&c_dfDIKeyboard);
  hResult = m_DirectInputDevice->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
  
  DIPROPDWORD dipdw;
  ZeroMemory(&dipdw, sizeof(dipdw));

  // Init dipdw
  dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
  dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
  dipdw.diph.dwObj        = 0;
  dipdw.diph.dwHow        = DIPH_DEVICE;
  dipdw.dwData            = KEYBOARD_BUFFER_SIZE;
  hResult = m_DirectInputDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
  if (hResult != DI_OK)
    return DEBUG_MSG(L"[ERROR] IDirectInputDevice8::SetProperty failed\n");

  hResult = m_DirectInputDevice->Acquire();
  if (hResult != DI_OK)
    return DEBUG_MSG(L"[ERROR] DINPUT8::Acquire failed!\n");
  DEBUG_MSG(L"[INFO] Keyboard has been initialized successfully\n");
}

void Input::ProcKeyboard()
{
  HRESULT hResult;

  hResult = m_DirectInputDevice->GetDeviceState(sizeof(m_KeyStates), m_KeyStates);
  if (FAILED(hResult))
  {
    if ((hResult == DIERR_INPUTLOST) || (hResult == DIERR_NOTACQUIRED))
    {
      if ((m_DirectInputDevice->Acquire()) == DI_OK)
        DEBUG_MSG(L"[INFO] Keyboard re-acquired!\n");
    }
    else DEBUG_MSG(L"[ERROR] DINPUT::GetDeviceState failed. Error: %d\n", hResult);

    return; 
  }

  m_KeyHandler->KeyState((BYTE*)&m_KeyStates);

  // Collect all buffered events
  DWORD dwElements = KEYBOARD_BUFFER_SIZE;
  hResult = m_DirectInputDevice->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_KeyEvents, &dwElements, 0);
  if (FAILED(hResult))
    return DEBUG_MSG(L"[ERROR] DINPUT::GetDeviceData failed. Error: %d\n", hResult);

  // Scan through all buffered events, check if the key is pressed or released
  for (DWORD i = 0; i < dwElements; i++)
  {
    int code = m_KeyEvents[i].dwOfs;
    int state = m_KeyEvents[i].dwData;
    if ((state & 0x80) > 0)
      m_KeyHandler->OnKeyDown(code);
    else
      m_KeyHandler->OnKeyUp(code);
  }
}

bool Input::IsKeyDown(int keycode)
{
  if (m_KeyStates == nullptr)
    return false;
  return (m_KeyStates[keycode] & 0x80);
}

Input* Input::GetInstance()
{
  return m_Instance.get();
}
